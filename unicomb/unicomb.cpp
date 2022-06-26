/*
  unicomb.cpp: comb filter with feedback and feedforward

  Copyright (C) 2022 Leonardo Foletto
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

#define MAXDELAY 1

/*
 Parameters: 
 [0] : input
 [1] : blend (-1 - 1) dry signal amount
 [2] : feedback (-1 - 1)
 [3] : feedforward (-1 - 1)
 [4] : feedback delay (ms)
 [5] : feedforward delay (ms)
*/

struct UniComb : csnd::Plugin<1, 6> 
{
  MYFLT blend;
  MYFLT feedback;
  MYFLT feedforward;
  int fbdelay;
  int ffdelay; 
  MYFLT maxdelay;
  csnd::AuxMem<MYFLT> fb_delay_buffer;
  csnd::AuxMem<MYFLT>::iterator fb_delay_iter;
  csnd::AuxMem<MYFLT> ff_delay_buffer;
  csnd::AuxMem<MYFLT>::iterator ff_delay_iter;
  
  int init() 
  {
    int maxdelay = csound->sr() * MAXDELAY;
    // fbdelay = int(inargs[4]*csound->sr()*0.001);
    // ffdelay = inargs[5]*csound->sr()*0.001;
    fb_delay_buffer.allocate(csound, maxdelay);
    ff_delay_buffer.allocate(csound, maxdelay);
    fb_delay_iter = fb_delay_buffer.begin();
    ff_delay_iter = ff_delay_buffer.begin();
    return OK;
  }
  
  int aperf() 
  {
    csnd::AudioSig in(this, inargs(0));
    csnd::AudioSig out(this, outargs(0));
    blend = inargs[1];
    feedback = inargs[2];
    feedforward = inargs[3];
    fbdelay = int(inargs[4]*csound->sr()*0.001);
    ffdelay = int(inargs[5]*csound->sr()*0.001);

    std::transform(in.begin(), in.end(), out.begin(), [this] (MYFLT s)
    {
      auto delayed_iter_ff = ff_delay_iter - ffdelay;
      auto delayed_iter_fb = fb_delay_iter - fbdelay;
      MYFLT ff = *delayed_iter_ff * feedforward;
      *ff_delay_iter = s;
      if(++ff_delay_iter == ff_delay_buffer.end())
      ff_delay_iter = ff_delay_buffer.begin();
      MYFLT fb = *delayed_iter_fb * feedback;
      MYFLT y = fb + ff + s * blend; 
      *fb_delay_iter = y;
      if(++fb_delay_iter == fb_delay_buffer.end())
      fb_delay_iter = fb_delay_buffer.begin();
      return y;
    });
    return OK;
  }

};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<UniComb>(csound, "unicomb", "a", "akkkkk", csnd::thread::ia);
}