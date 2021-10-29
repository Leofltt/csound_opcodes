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

// inargs : amplitude, cps, osc table, phase table

struct PDOsc : csnd::Plugin<1, 4> {
  
  csnd::Table phase_table;
  csnd::Table osc_table;
  double idp,idx;
  double s,z;
  double sr;

  int init() {
    phase_table.init(csound, inargs(3));
    osc_table.init(csound, inargs(2));
    s = phase_table.len();
    z = osc_table.len();
    sr = csound->sr();
    idp = 0.;
    idx = 0.;
    return OK;
  }

  int aperf() {
    csnd::AudioSig out(this, outargs(0));
    MYFLT amp = inargs[0];
    MYFLT freq = inargs[1];
    MYFLT ph = freq / sr;
    for (auto &sample : out) {
      idx = phase_table[(uint32_t)(idp * s)];
      sample = amp * osc_table[(uint32_t)(idx * z)];
      idp += ph;
      while (idp < 0.)
        idp += 1.;
      while (idp >= 1.)
        idp -= 1.;
    }
    return OK;
  }
};

#include <modload.h>

void csnd::on_load(Csound *csound) {
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "ikii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iaii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kkii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "akii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kaii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aaii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "ikii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aiii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "iaii", csnd::thread::ia);
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kkii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "akii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "kaii", csnd::thread::ia); 
  csnd::plugin<PDOsc>(csound, "pdosc", "a", "aaii", csnd::thread::ia); 
}