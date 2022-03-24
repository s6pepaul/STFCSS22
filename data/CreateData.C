#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"

void CreateData(){

    TFile* outfile = new TFile("data_ex2.root", "RECREATE");
    TH1F* h1 = new TH1F("h1","",400,-20,20);
    TH1F* h2 = new TH1F("h2","",400,-20,20);
    TH1F* h3 = new TH1F("h3","",400,-20,20);
    TH1F* h4 = new TH1F("h4","",400,-20,20);
    TH1F* h5 = new TH1F("h5","",400,-20,20);
	TF1* f1 = new TF1("f1","gaus(0)",-20,20);
	TF1* f2 = new TF1("f2","pol2(0)",-20,20);
	f1->SetParameters(1,5,1);
	h1->FillRandom("f1",5000);
    h1->Write();

	f1->SetParameters(1,0,0.5);
	f2->SetParameters(100,2,0);
	h2->FillRandom("f1",7500);
	h2->FillRandom("f2",8000);
    h2->Write();

	f1->SetParameters(1,10,1);
	f2->SetParameters(100,3,0);
	h3->FillRandom("f1",3200);
	h3->FillRandom("f2",23000);
    h3->Write();

	f1->SetParameters(1,1,4);
	f2->SetParameters(100,1,0);
	h4->FillRandom("f1",11700);
	h4->FillRandom("f2",15000);
    h4->Write();

	f1->SetParameters(1,-3,2);
	f2->SetParameters(100,1.3,3);
	h5->FillRandom("f1",2800);
	h5->FillRandom("f2",5000);
    h5->Write();


    outfile->Close();


}