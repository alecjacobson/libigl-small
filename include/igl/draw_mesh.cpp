// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "draw_mesh.h"
#ifndef IGL_NO_OPENGL

IGL_INLINE void igl::draw_mesh(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & N)
{
  using namespace Eigen;
  MatrixXd _d;
  MatrixXi _i;
  return draw_mesh(V,F,N,_i,_d,_d,_i,_d,0,_i,0);
}

IGL_INLINE void igl::draw_mesh(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & N,
  const Eigen::MatrixXd & C)
{
  using namespace Eigen;
  MatrixXd _d;
  MatrixXi _i;
  return draw_mesh(V,F,N,_i,C,_d,_i,_d,0,_i,0);
}

IGL_INLINE void igl::draw_mesh(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & N,
  const Eigen::MatrixXd & C,
  const Eigen::MatrixXd & TC)
{
  using namespace Eigen;
  MatrixXd _d;
  MatrixXi _i;
  return draw_mesh(V,F,N,_i,C,TC,_i,_d,0,_i,0);
}

IGL_INLINE void igl::draw_mesh(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & N,
  const Eigen::MatrixXd & C,
  const Eigen::MatrixXd & TC,
  const Eigen::MatrixXd & W,
  const GLuint W_index,
  const Eigen::MatrixXi & WI,
  const GLuint WI_index)
{
  using namespace Eigen;
  return draw_mesh(V,F,N,MatrixXi(),C,TC,MatrixXi(),W,W_index,WI,WI_index);
}

IGL_INLINE void igl::draw_mesh(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & N,
  const Eigen::MatrixXi & NF,
  const Eigen::MatrixXd & C,
  const Eigen::MatrixXd & TC,
  const Eigen::MatrixXi & TF,
  const Eigen::MatrixXd & W,
  const GLuint W_index,
  const Eigen::MatrixXi & WI,
  const GLuint WI_index)
{
  using namespace std;
  using namespace Eigen;
  const int rF = F.rows();
  const int cC = C.cols();
  const int rC = C.rows();
  const int cW = W.cols();
  const int rW = W.rows();
  const int rV = V.rows();
  const int rTC = TC.rows();
  const int rTF = TF.rows();
  const int rNF = NF.rows();
  const int rN = N.rows();

  if(F.size() > 0)
  {
    assert(F.maxCoeff() < V.rows());
    assert(V.cols() == 3);
    assert(C.rows() == V.rows() || C.rows() == F.rows()*3 || C.size() == 0);
    assert(C.cols() == 3 || C.size() == 0);
    assert(N.cols() == 3);
    assert(TC.cols() == 2 || TC.size() == 0);
  }
  if(W.size()>0)
  {
    assert(W.rows() == V.rows());
    assert(WI.rows() == V.rows());
    assert(W.cols() == WI.cols());
  }

  glBegin(GL_TRIANGLES);
  // loop over faces
  for(int i = 0; i<rF;i++)
  {
    // loop over corners of triangle
    for(int j = 0;j<3;j++)
    {

      int tc = -1;
      if(rTF != 0)
      {
        tc = TF(i,j);
      } else if(rTC == 1)
      {
        tc = 0;
      }else if(rTC == rV)
      {
        tc = F(i,j);
      }else if(rTC == rF*2)
      {
        tc = i*2 + j;
      }else if(rTC == rF)
      {
        tc = i;
      }else
      {
        assert(TC.size() == 0);
      }

      // RGB(A)
      Matrix<MatrixXd::Scalar,1,Dynamic> color;
      if(rC == 1)
      {
        color = C.row(0);
      }else if(rC == rV)
      {
        color = C.row(F(i,j));
      }else if(rC == rF*3)
      {
        color = C.row(i*3+j);
      }else if(rC == rF)
      {
        color = C.row(i);
      }else
      {
        assert(C.size() == 0);
      }

      int n = -1;
      if(rNF != 0)
      {
        n = NF(i,j);
      } else if(rN == 1)
      {
        n = 0;
      }else if(rN == rV)
      {
        n = F(i,j);
      }else if(rN == rF*2)
      {
        n = i*2 + j;
      }else if(rN == rF)
      {
        n = i;
      }else
      {
        assert(N.size() == 0);
      }

      {
        if(rW>0 && W_index !=0 && WI_index != 0)
        {
          int weights_left = cW;
          while(weights_left != 0)
          {
            int pass_size = std::min(4,weights_left);
            int weights_already_passed = cW-weights_left;
            // Get attribute location of next 4 weights
            int pass_W_index = W_index + weights_already_passed/4;
            int pass_WI_index = WI_index + weights_already_passed/4;
            switch(pass_size)
            {
              case 1:
                glVertexAttrib1d(
                  pass_W_index,
                  W(F(i,j),0+weights_already_passed));
                glVertexAttrib1d(
                  pass_WI_index,
                  WI(F(i,j),0+weights_already_passed));
                break;
              case 2:
                glVertexAttrib2d(
                  pass_W_index,
                  W(F(i,j),0+weights_already_passed),
                  W(F(i,j),1+weights_already_passed));
                glVertexAttrib2d(
                  pass_WI_index,
                  WI(F(i,j),0+weights_already_passed),
                  WI(F(i,j),1+weights_already_passed));
                break;
              case 3:
                glVertexAttrib3d(
                  pass_W_index,
                  W(F(i,j),0+weights_already_passed),
                  W(F(i,j),1+weights_already_passed),
                  W(F(i,j),2+weights_already_passed));
                glVertexAttrib3d(
                  pass_WI_index,
                  WI(F(i,j),0+weights_already_passed),
                  WI(F(i,j),1+weights_already_passed),
                  WI(F(i,j),2+weights_already_passed));
                break;
              default:
                glVertexAttrib4d(
                  pass_W_index,
                  W(F(i,j),0+weights_already_passed),
                  W(F(i,j),1+weights_already_passed),
                  W(F(i,j),2+weights_already_passed),
                  W(F(i,j),3+weights_already_passed));
                glVertexAttrib4d(
                  pass_WI_index,
                  WI(F(i,j),0+weights_already_passed),
                  WI(F(i,j),1+weights_already_passed),
                  WI(F(i,j),2+weights_already_passed),
                  WI(F(i,j),3+weights_already_passed));
                break;
            }
            weights_left -= pass_size;
          }
        }
        if(tc != -1)
        {
          glTexCoord2d(TC(tc,0),TC(tc,1));
        }
        if(rC>0)
        {
          switch(cC)
          {
            case 3:
              glColor3dv(color.data());
              break;
            case 4:
              glColor4dv(color.data());
              break;
            default:
              break;
          }
        }
        if(n != -1)
        {
          glNormal3d(N(n,0),N(n,1),N(n,2));
        }
        glVertex3d(V(F(i,j),0),V(F(i,j),1),V(F(i,j),2));
      }
    }
  }
  glEnd();
}

#endif
