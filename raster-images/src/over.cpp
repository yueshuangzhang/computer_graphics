#include "over.h"
#include <iostream>
void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // A over B, source over dst
  // Over: [source] = s; [dst] = d; [both] = s
  // A_src⋅[as]+A_dst⋅[ad]+A_both⋅[ab]
  // Asrc=αs⋅(1−αd)
  // Adst=αd⋅(1−αs)
  // Aboth=αs⋅αd
  // lecture slides & http://ssp.impulsetrain.com/porterduff.html

  // inputs are rgba, therefore, 4 channels
  int track = 0;
  for (int a = 0; a < A.size(); a+=4){//dest
    double alpha_src, alpha_dst;
    unsigned char A_src, A_dst, A_both;
    unsigned char r_s, g_s, b_s, r_d, g_d, b_d;
    r_s = A[a + 0];
    g_s = A[a + 1];
    b_s = A[a + 2];
    r_d = B[a + 0];
    g_d = B[a + 1];
    b_d = B[a + 2];

    alpha_src = A[a + 3]/double(255); //rgba
    alpha_dst = B[a + 3]/double(255); //rgba

    A_src = alpha_src * (1 - alpha_dst);
    A_dst = alpha_dst * (1 - alpha_src);
    A_both = alpha_src * alpha_dst;

    //determine source/both/neither/dst
    if (alpha_src == 0  && alpha_dst == 0){//neither
      C[track + 0] = 0;
      C[track + 1] = 0;
      C[track + 2] = 0;
      C[track + 3] = 0;
    }
    else if (alpha_src == 0  && alpha_dst != 0){//dest
      C[track + 0] = r_d;
      C[track + 1] = g_d;
      C[track + 2] = b_d;
      C[track + 3] = alpha_dst * 255;
    }
    else if (alpha_src != 0  && alpha_dst != 0){//both
      C[track + 0] = r_s * alpha_src + r_d * (1-alpha_src) * alpha_dst;
      C[track + 1] = g_s * alpha_src + g_d * (1-alpha_src) * alpha_dst;
      C[track + 2] = b_s * alpha_src + b_d * (1-alpha_src) * alpha_dst;
      C[track + 3] = (alpha_src + (1 - alpha_src)*alpha_dst) * 255;
    }
    else if (alpha_src != 0  && alpha_dst == 0){//src
      C[track + 0] = r_s;
      C[track + 1] = g_s;
      C[track + 2] = b_s;
      C[track + 3] = alpha_src * 255;
    }
    track += 4;
  }
  ////////////////////////////////////////////////////////////////////////////
}
