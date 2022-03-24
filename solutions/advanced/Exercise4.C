#define Exercise4_cxx
// The class definition in Exercise4.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Exercise4.C")
// root> T->Process("Exercise4.C","some options")
// root> T->Process("Exercise4.C+")
//


#include "Exercise4.h"
#include <TH2.h>
#include <TStyle.h>

void Exercise4::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   hist_m1 = new TH1F("hist_m1",";m1",200,0,20);
   hist_m2 = new TH1F("hist_m2",";m2",200,0,20);
   hist_m3 = new TH1F("hist_m3",";m3",200,0,20);
   hist_m4 = new TH1F("hist_m4",";m4",200,-5,5);
   hist_m5 = new TH1F("hist_m5",";m5",200,-5,5);
}

void Exercise4::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Exercise4::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);

   hist_m1->Fill(*m1);
   hist_m2->Fill(*m2);
   hist_m3->Fill(*m3);
   hist_m4->Fill(*m4);
   hist_m5->Fill(*m5);

   return kTRUE;
}

void Exercise4::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Exercise4::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   TFile* out = new TFile("ResultsEx4.root","RECREATE");

	TF1* f1 = new TF1("f1","[0]*TMath::Gaus(x,[1],[2])",0,20);
   f1->SetParameters(100,1.5,0.2);
   f1->SetParLimits(2,0,1000);
   hist_m1->Fit(f1);
   hist_m1->Write();

   TF1* f2 = new TF1("f2","[0]*TMath::Gaus(x,[1],[2])",0,20);
   f2->SetParameters(100,5,2);
   f2->SetParLimits(2,0,1000);
   hist_m2->Fit(f2);
   hist_m2->Write();

   TF1* f3 = new TF1("f3","[0]*TMath::Gaus(x,[1],[2])",0,20);
   f3->SetParameters(100,2,0.5);
   f3->SetParLimits(2,0,1000);
   hist_m3->Fit(f3);
   hist_m3->Write();

   TF1* f4 = new TF1("f4","[0]*TMath::Cos([1]*x+[2])+[3]",-5,5);
   f4->SetParameters(100,2,0.1,100);
   hist_m4->Fit(f4);
   hist_m4->Write();

   TF1* f5 = new TF1("f5","[0]*TMath::Cos([1]*x+[2])+[3]",-5,5);
   f5->SetParameters(100,4,0.1,100);
   f5->SetParLimits(0,0,1E6);
   hist_m5->Fit(f5);
   hist_m5->Write();
   out->Close();
}