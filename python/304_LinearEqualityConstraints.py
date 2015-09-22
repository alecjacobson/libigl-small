import igl

V = igl.eigen.MatrixXd()
F = igl.eigen.MatrixXi()

igl.readOFF("../tutorial/shared/cheburashka.off",V,F)

# Two fixed points
# Left hand, left foot
b = igl.eigen.MatrixXi([[4331],[5957]])
bc = igl.eigen.MatrixXd([[1],[-1]])

# Construct Laplacian and mass matrix
L = igl.eigen.SparseMatrixd()
M = igl.eigen.SparseMatrixd()
Minv = igl.eigen.SparseMatrixd()
Q = igl.eigen.SparseMatrixd()

igl.cotmatrix(V,F,L)
igl.massmatrix(V,F,igl.MASSMATRIX_TYPE_VORONOI,M)
igl.invert_diag(M,Minv)

# Bi-Laplacian
Q = L * (Minv * L);

# Zero linear term
B = igl.eigen.MatrixXd.Zero(V.rows(),1);

Z       = igl.eigen.MatrixXd()
Z_const = igl.eigen.MatrixXd()

# Alternative, short hand
mqwf = igl.min_quad_with_fixed_data()

# Empty constraints
Beq = igl.eigen.MatrixXd()
Aeq = igl.eigen.SparseMatrixd()

igl.min_quad_with_fixed_precompute(Q,b,Aeq,True,mqwf)
igl.min_quad_with_fixed_solve(mqwf,B,bc,Beq,Z)

# Constraint forcing difference of two points to be 0
Aeq = igl.eigen.SparseMatrixd(1,V.rows())

# Right hand, right foot
Aeq.insert(0,6074,1)
Aeq.insert(0,6523,-1)
Aeq.makeCompressed()

Beq = igl.eigen.MatrixXd([[0]])
igl.min_quad_with_fixed_precompute(Q,b,Aeq,True,mqwf)
igl.min_quad_with_fixed_solve(mqwf,B,bc,Beq,Z_const)

# Pseudo-color based on solution
global C
C = igl.eigen.MatrixXd()

global C_const
C_const = igl.eigen.MatrixXd()

global toggle
toggle = True

# Use same color axes
min_z = min(Z.minCoeff(),Z_const.minCoeff())
max_z = max(Z.maxCoeff(),Z_const.maxCoeff())

igl.jet(      Z,min_z,max_z,C);
igl.jet(Z_const,min_z,max_z,C_const);

# Plot the mesh with pseudocolors
viewer = igl.viewer.Viewer()
viewer.data.set_mesh(V, F)
viewer.core.show_lines = False
viewer.data.set_colors(C)

def key_down(viewer,key,mode):
    if key == ord(' '):
        global toggle
        global C
        global C_const

        if toggle:
            viewer.data.set_colors(C)
        else:
            viewer.data.set_colors(C_const)

        toggle = not toggle;
        return True

    return False

viewer.callback_key_down = key_down

print("Press [space] to toggle between unconstrained and constrained.")
viewer.launch()
