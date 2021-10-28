/*
  pan3.cpp: 3 stereo panning algorithms

  Copyright (C) 2021 Leonardo Foletto
  This file is part of Csound.

  The Csound Library is free software; you can redistribute it
  and/or modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  Csound is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with Csound; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
  02110-1301 USA
*/

#include <plugin.h>

#define PIHALF  M_PI/2

/*
 Parameters: 
 [0] : left input, [1] : right input
 [2] : control value 0 - 1 (left to right / mid to side)
 [3] : modes : 0 - constant power sin, 1 - constant power sqrt, 2 - mid/size
*/

struct Pan3 : csnd::Plugin<2, 4> {

  int mode;
  MYFLT control;
  
  int init() {
    mode = inargs[3];
    return OK;
  }
  
  int aperf() {
    control = inargs[2];
    for (int i=offset; i < nsmps; i++) {
      switch(mode) {
          case 0:
          default:
          {
            outargs(0)[i] = inargs(0)[i] * sin(1-control * PIHALF);
            outargs(1)[i] = inargs(1)[i] * sin(control * PIHALF);
          } break;
          case 1:
          {
            outargs(0)[i] = inargs(0)[i] * sqrt(1-control);
            outargs(1)[i] = inargs(1)[i] * sqrt(control);
          } break;
          case 2:
          {
            MYFLT mid = inargs(0)[i] + inargs(1)[i];
            MYFLT side = inargs(0)[i] - inargs(1)[i];
            mid *= 0.5;
            side *= 0.5; 
            mid *= (1 - control);
            side *= control; 
            MYFLT ms_left = mid + side;
            MYFLT ms_right = mid - side;
            outargs(0)[i] = ms_left;
            outargs(1)[i] = ms_right;
          } break;
      }
    }
    return OK;
  }
  
};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<Pan3>(csound, "pan3", "aa", "aaai", csnd::thread::ia); 
  csnd::plugin<Pan3>(csound, "pan3", "aa", "aaki", csnd::thread::ia);
}