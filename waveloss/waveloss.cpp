/*
  waveloss.cpp: waveloss UGen from sc3-plugins ( https://doc.sccode.org/Classes/WaveLoss.html )
                implemented as Csound opcode

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
#include <random>

/*
 Divide an audio stream into tiny segments, using the signal's zero-crossings as segment boundaries, and discard a fraction of them (i.e. replace them with silence of the same length). The technique was described by Trevor Wishart in a lecture.
 Parameters: the filter drops [1] out of [2] chunks. 
 [3] can be 0 to drop chunks in a simple deterministic fashion (e.g. always dropping the first 30 out of a set of 40 segments), or 1 to drop chunks randomly but in an appropriate proportion.
*/

struct Waveloss : csnd::Plugin<1, 4> 
{

  uint32_t drop;
  uint32_t max;
  uint32_t count;
  bool on;
  int mode;
  MYFLT previous_sample;  
  std::random_device rdev;

  int init() 
  {
    previous_sample = 0.;
    on = 1;
    count = 0;
    mode = inargs[3];
    return OK;
  }
  
  int aperf() 
  {
    csnd::AudioSig in(this, inargs(0));
    csnd::AudioSig out(this, outargs(0));
    drop = inargs[1];
    max = inargs[2];
    for (int i=offset; i < nsmps; i++) 
    {
      if (previous_sample <= 0 && in[i] >=0) 
      {
        if (mode == 1) 
        {
          std::mt19937 generator(rdev());
          std::uniform_int_distribution<uint32_t> distribution(0,max);
          uint32_t random_value = distribution(generator);
          on = random_value >= drop;
        } else 
        {
          count = count >= max ? 0 : ++count ;
          on = count >= drop;
        }
      }
      previous_sample = in[i];
      out[i] = in[i] * on;
    }
    return OK;
  }
  
};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<Waveloss>(csound, "waveloss", "a", "akki", csnd::thread::ia); 
  csnd::plugin<Waveloss>(csound, "waveloss", "a", "akii", csnd::thread::ia);
  csnd::plugin<Waveloss>(csound, "waveloss", "a", "aiki", csnd::thread::ia); 
  csnd::plugin<Waveloss>(csound, "waveloss", "a", "aiii", csnd::thread::ia); 
}