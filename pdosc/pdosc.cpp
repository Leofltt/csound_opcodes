/*
  pdosc.cpp: phase distortion oscillator

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

// inargs : amplitude, cps, table

struct PDOsc : csnd::Plugin<1, 3> {
  
  csnd::Table table;
  double scl;
  double idx;

  int init() {
    table.init(csound, inargs(2));
    scl = table.len() / csound->sr();
    idx = 0.;
    return OK;
  }

  int aperf() {
    csnd::AudioSig out(this, outargs(0));
    MYFLT amp = inargs[0];
    MYFLT si = inargs[1] * scl;
    for (auto &sample : out) {
      sample = amp * table[(uint32_t)idx];
      idx += si;
      while (idx < 0)
        idx += table.len();
      while (idx >= table.len())
        idx -= table.len();
    }
    return OK;
  }
};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iki", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iai", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kki", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aki", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kai", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aai", csnd::thread::ia); 
}