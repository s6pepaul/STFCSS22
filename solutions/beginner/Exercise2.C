#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"

void Exercise2(){
	
	/***** PART 1 ******/
	TCanvas* c1 = new TCanvas("c1","Exercise2a");
	TH1F* h1 = new TH1F("h1","",100,0,10);
	TF1* f1 = new TF1("f1","gaus(0)",0,10);
	f1->SetParameter(0,1);
	f1->SetParameter(1,5);
	f1->SetParameter(2,1);

	h1->FillRandom("f1",5000);
	h1->Draw();
	
	/***** PART 2 ******/
	TCanvas* c2 = new TCanvas("c2","Exercise2b");
	h1->Draw();
	TH1F* h2 = new TH1F("h2","",100,0,10);
	TF1* f2 = new TF1("f2","pol1(0)",0,10);
	f2->SetParameter(0,20);
	f2->SetParameter(1,2);
	h2->FillRandom("f2",5000);
	h2->SetLineColor(kRed);
	h2->Draw("SAME");
	
	TH1F* h3 = new TH1F("h3","",100,0,10);
	TF1* f3 = new TF1("f3","gaus(0)+pol1(3)",0,10);
	f3->SetParameters(119.68,5,1,20,2); //normalise gaussian such that integrals from 0 to 10 are equal
	h3->FillRandom("f3",10000);
	h3->SetLineColor(kGreen);
	h3->Draw("SAME");
	
	h1->GetYaxis()->SetRangeUser(0,1.2*h3->GetMaximum());
	
	/******* Save results ********/
	c1->SaveAs("Exercise2a.png");
	c2->SaveAs("Exercise2b.png");
	
}
