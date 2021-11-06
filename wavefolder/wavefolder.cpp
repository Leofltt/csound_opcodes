/*
  wavefolder.cpp: wavefolder based on https://ccrma.stanford.edu/~jatin/ComplexNonlinearities/Wavefolder.html 
                  by Jatin Chowdhury

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

#define TWOPI M_PI*2.0

/*
 Parameters: 
 [0] : input
 [1] : trim (gain of folded path)
 [2] : feedback (0 - 1)
 [3] : feedforward (0 - 1)
 [4] : control (0 - 1) 
 [5] : mode (0 for sine folding, 1 for triangle folding)
*/

struct Wavefolder : csnd::Plugin<1, 6> 
{
  MYFLT trim;
  MYFLT feedback;
  MYFLT feedforward;
  MYFLT control; 
  int mode;
  MYFLT previous_sample;
  
  int init() 
  {
    previous_sample = 0.;
    mode = inargs[5];
    return OK;
  }
  
  int aperf() 
  {
    csnd::AudioSig in(this, inargs(0));
    csnd::AudioSig out(this, outargs(0));
    trim = inargs[1];
    feedback = inargs[2];
    feedforward = inargs[3];
    control = inargs[4];
    control <= 0 ? control = 0.001 : control = control;
    control >= 1 ? control = 1 : control = control;
    control *= 0.5; 
    for (int i=offset; i < nsmps; i++) 
    {
        if (mode == 1) // triangle fold
        {
          MYFLT p = 1.0 / control;
          MYFLT x = in[i] + p / 4.;
          out[i] = 4. * abs(x / p - floor(x / p + 0.5)) - 1.; 
        } else // sine fold (default)
        {
          MYFLT x = in[i];
          out[i] = sin(TWOPI * x * control); 
        }
        MYFLT y = tanh(in[i]) * feedforward;
        y += tanh(previous_sample * feedback);
        out[i] *= trim;
        out[i] += y;
        previous_sample = out[i];
    }
    return OK;
  }

};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akkkki", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akkkii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aikkki", csnd::thread::ia); 
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akkiii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aikkii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aiikki", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akiiii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aikiii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aiikii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aiiiki", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akikii", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aikiki", csnd::thread::ia);
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "akiiki", csnd::thread::ia); 
  csnd::plugin<Wavefolder>(csound, "wavefolder", "a", "aiiiii", csnd::thread::ia); 
}