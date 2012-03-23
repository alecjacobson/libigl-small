#include "mosek_quadprog.h"
#include "mosek_guarded.h"
#include <cstdio>
#include "../verbose.h"

// Little function mosek needs in order to know how to print to std out
static void MSKAPI printstr(void *handle, char str[])
{
  printf("%s",str);
}

template <typename Index, typename Scalar>
IGL_INLINE bool igl::mosek_quadprog(
  const Index n,
  const std::vector<Index> & Qi,
  const std::vector<Index> & Qj,
  const std::vector<Scalar> & Qv,
  const std::vector<Scalar> & c,
  const Scalar cf,
  const Index m,
  const std::vector<Index> & Ari,
  const std::vector<Index> & Acp,
  const std::vector<Scalar> & Av,
  const std::vector<Scalar> & lc,
  const std::vector<Scalar> & uc,
  const std::vector<Scalar> & lx,
  const std::vector<Scalar> & ux,
  std::vector<Scalar> & x)
{
  // I J V vectors of Q should all be same length
  assert(Qv.size() == Qi.size());
  assert(Qv.size() == Qj.size());
  // number of columns in linear constraint matrix must be ≤ number of
  // variables
  assert(Acp.size() == (n+1));
  // linear bound vectors must be size of number of constraints or empty
  assert( (lc.size() == m) || (lc.size() == 0));
  assert( (uc.size() == m) || (uc.size() == 0));
  // constant bound vectors must be size of number of variables or empty
  assert( (lx.size() == n) || (lx.size() == 0));
  assert( (ux.size() == n) || (ux.size() == 0));

  // allocate space for solution in x
  x.resize(n);

  // variables for mosek task, env and result code
  MSKenv_t env;
  MSKtask_t task;

  // Create the MOSEK environment
  mosek_guarded(MSK_makeenv(&env,NULL,NULL,NULL,NULL));
  /* Directs the log stream to the 'printstr' function. */
  mosek_guarded(MSK_linkfunctoenvstream(env,MSK_STREAM_LOG,NULL,printstr));
  // initialize mosek environment
  mosek_guarded(MSK_initenv(env));
  // Create the optimization task
  mosek_guarded(MSK_maketask(env,m,n,&task));
  verbose("Creating task with %ld linear constraints and %ld variables...\n",m,n);
  // Tell mosek how to print to std out
  mosek_guarded(MSK_linkfunctotaskstream(task,MSK_STREAM_LOG,NULL,printstr));
  // Give estimate of number of variables
  mosek_guarded(MSK_putmaxnumvar(task,n));
  if(m>0)
  {
    // Give estimate of number of constraints
    mosek_guarded(MSK_putmaxnumcon(task,m));
    // Give estimate of number of non zeros in A
    mosek_guarded(MSK_putmaxnumanz(task,Av.size()));
  }
  // Give estimate of number of non zeros in Q
  mosek_guarded(MSK_putmaxnumqnz(task,Qv.size()));
  if(m>0)
  {
    // Append 'm' empty constraints, the constrainst will initially have no
    // bounds
    mosek_guarded(MSK_append(task,MSK_ACC_CON,m));
  }
  // Append 'n' variables
  mosek_guarded(MSK_append(task,MSK_ACC_VAR,n));
  // add a contant term to the objective
  mosek_guarded(MSK_putcfix(task,cf));

  // loop over variables
  for(int j = 0;j<n;j++)
  {
    if(c.size() > 0)
    {
      // Set linear term c_j in the objective
      mosek_guarded(MSK_putcj(task,j,c[j]));
    }

    // Set constant bounds on variable j
    if(lx[j] == ux[j])
    {
      mosek_guarded(MSK_putbound(task,MSK_ACC_VAR,j,MSK_BK_FX,lx[j],ux[j]));
    }else
    {
      mosek_guarded(MSK_putbound(task,MSK_ACC_VAR,j,MSK_BK_RA,lx[j],ux[j]));
    }

    if(m>0)
    {
      // Input column j of A
      mosek_guarded(
        MSK_putavec(
          task,
          MSK_ACC_VAR,
          j,
          Acp[j+1]-Acp[j],
          &Ari[Acp[j]],
          &Av[Acp[j]])
        );
    }
  }

  // loop over constraints
  for(size_t i = 0;i<m;i++)
  {
    // put bounds  on constraints
    mosek_guarded(MSK_putbound(task,MSK_ACC_CON,i,MSK_BK_RA,lc[i],uc[i]));
  }

  // Input Q for the objective (REMEMBER Q SHOULD ONLY BE LOWER TRIANGLE)
  mosek_guarded(MSK_putqobj(task,Qv.size(),&Qi[0],&Qj[0],&Qv[0]));

  //// Set up task parameters

  // set tolerance
  //mosek_guarded(
  //  MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_DFEAS,1e-8));
  //mosek_guarded(
  //  MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_DSAFE,1.0));
  // 1.0 means optimizer is very leniant about declaring model infeasible
  //mosek_guarded(
  //  MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_INFEAS,1e-8));
  //mosek_guarded(
  //  MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_PATH,1e-8));
  //mosek_guarded(
  //  MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_PFEAS,1e-8));

  // Hard to say if this is doing anything, probably nothing dramatic
  mosek_guarded(MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_PSAFE,1e2));

  // >1e0 NONSOLUTION
  // 1e-1 artifacts in deformation
  // 1e-3 artifacts in isolines
  // 1e-4 seems safe
  // 1e-8 MOSEK DEFAULT SOLUTION
  mosek_guarded(MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_REL_GAP,1e-8));
  //mosek_guarded(MSK_putdouparam(task,MSK_DPAR_INTPNT_TOL_REL_STEP,0.9999));

  // Turn off presolving
  //mosek_guarded(
  //  MSK_putintparam(task,MSK_IPAR_PRESOLVE_USE,MSK_PRESOLVE_MODE_OFF));

  // Force particular matrix reordering method
  // MSK_ORDER_METHOD_NONE cuts time in half roughly, since half the time is
  //   usually spent reordering the matrix
  // !! WARNING Setting this parameter to anything but MSK_ORDER_METHOD_FREE
  //   seems to have the effect of setting it to MSK_ORDER_METHOD_NONE
  //   *Or maybe Mosek is spending a bunch of time analyzing the matrix to
  //   choose the right ordering method when really any of them are
  //   instantaneous
  mosek_guarded(
    MSK_putintparam(task,MSK_IPAR_INTPNT_ORDER_METHOD,MSK_ORDER_METHOD_NONE));

  // Turn off convexity check
  mosek_guarded(
    MSK_putintparam(task,MSK_IPAR_CHECK_CONVEXITY,MSK_CHECK_CONVEXITY_NONE));

  // Force using multiple threads, not sure if MOSEK is properly destorying
  //extra threads...
  mosek_guarded(MSK_putintparam(task,MSK_IPAR_INTPNT_NUM_THREADS,6));
  
  // Force turn off data check
  mosek_guarded(MSK_putintparam(task,MSK_IPAR_DATA_CHECK,MSK_OFF));

  // Now the optimizer has been prepared
  MSKrescodee trmcode;
  // run the optimizer
  mosek_guarded(MSK_optimizetrm(task,&trmcode));

  // Print a summary containing information about the solution for debugging
  // purposes
  MSK_solutionsummary(task,MSK_STREAM_LOG);

  // Get status of solution
  MSKsolstae solsta;
  MSK_getsolutionstatus(task,MSK_SOL_ITR,NULL,&solsta);

  bool success = false;
  switch(solsta)
  {
    case MSK_SOL_STA_OPTIMAL:   
    case MSK_SOL_STA_NEAR_OPTIMAL:
      MSK_getsolutionslice(task,MSK_SOL_ITR,MSK_SOL_ITEM_XX,0,n,&x[0]);
      printf("Optimal primal solution\n");
      //for(size_t j=0; j<n; ++j)
      //{
      //  printf("x[%ld]: %g\n",j,x[j]);
      //}
      success = true;
      break;
    case MSK_SOL_STA_DUAL_INFEAS_CER:
    case MSK_SOL_STA_PRIM_INFEAS_CER:
    case MSK_SOL_STA_NEAR_DUAL_INFEAS_CER:
    case MSK_SOL_STA_NEAR_PRIM_INFEAS_CER:  
      printf("Primal or dual infeasibility certificate found.\n");
      break;
    case MSK_SOL_STA_UNKNOWN:
      printf("The status of the solution could not be determined.\n");
      break;
    default:
      printf("Other solution status.");
      break;
  }

  MSK_deletetask(&task);
  MSK_deleteenv(&env);

  return success;
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
