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

#define PIHALF  M_PI/2.0

/*
 Parameters: 
 [0] : left input, [1] : right input
 [2] : control value 0 - 1 (left to right / mid to side)
 [3] : modes : 0 - constant power sin, 1 - constant power sqrt, 2 - mid/size
*/

struct Pan3 : csnd::Plugin<2, 4> 
{

  int mode;
  MYFLT control;
  
  int init() 
  {
    mode = inargs[3];
    return OK;
  }
  
  int aperf() 
  {
    csnd::AudioSig inL(this, inargs(0));
    csnd::AudioSig outL(this, outargs(0));
    csnd::AudioSig inR(this, inargs(1));
    csnd::AudioSig outR(this, outargs(1));
    control = inargs[2];
    for (int i=offset; i < nsmps; i++) 
    {
      switch(mode) 
      {
          case 0:
          default:
          {
            outL[i] = inL[i] * sin(1-control * PIHALF);
            outR[i] = inR[i] * sin(control * PIHALF);
          } break;
          case 1:
          {
            outL[i] = inL[i] * sqrt(1-control);
            outR[i] = inR[i] * sqrt(control);
          } break;
          case 2:
          {
            MYFLT mid = inL[i] + inR[i];
            MYFLT side = inL[i] - inR[i];
            mid *= 0.5;
            side *= 0.5; 
            mid *= (1 - control);
            side *= control; 
            MYFLT ms_left = mid + side;
            MYFLT ms_right = mid - side;
            outL[i] = ms_left;
            outR[i] = ms_right;
          } break;
      }
    }
    return OK;
  }
  
};

#include <modload.h>

void csnd::on_load(Csound *csound) 
{
  csnd::plugin<Pan3>(csound, "pan3", "aa", "aaai", csnd::thread::ia); 
  csnd::plugin<Pan3>(csound, "pan3", "aa", "aaki", csnd::thread::ia);
}