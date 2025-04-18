/// \file
/// \ingroup tutorial_hist
/// \notebook -js
/// \preview Strip chart example.
///
/// \macro_image
/// \macro_code
///
/// \author Rene Brun

#include "TStopwatch.h"
#include "TDatime.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TRandom.h"
#include <cstdio>

void hist063_TH1_seism()
{

   TStopwatch sw;
   sw.Start();
   // set time offset
   TDatime dtime;
   gStyle->SetTimeOffset(dtime.Convert());

   TCanvas *c1 = new TCanvas("c1", "Time on axis", 10, 10, 1000, 500);
   c1->SetGrid();

   Float_t bintime = 1; // one bin = 1 second. change it to set the time scale
   TH1F *ht = new TH1F("ht", "The ROOT seism", 10, 0, 10 * bintime);
   Float_t signalval = 1000;
   ht->SetMaximum(signalval);
   ht->SetMinimum(-signalval);
   ht->SetStats(false);
   ht->SetLineColor(2);
   ht->GetXaxis()->SetTimeDisplay(1);
   ht->GetYaxis()->SetNdivisions(520);
   ht->Draw();

   for (Int_t i = 1; i < 2300; i++) {
      //======= Build a signal : noisy damped sine ======
      Float_t noise = gRandom->Gaus(0, 120);
      if (i > 700)
         noise += signalval * sin((i - 700.) * 6.28 / 30) * exp((700. - i) / 300.);
      ht->SetBinContent(i, noise);
      c1->Modified();
      c1->Update();
      gSystem->ProcessEvents(); // canvas can be edited during the loop
   }
   printf("Real Time = %8.3fs, Cpu Time = %8.3fs\n", sw.RealTime(), sw.CpuTime());
}
