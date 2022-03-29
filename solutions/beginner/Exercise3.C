#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"

void Exercise3(){
	
	/***** PART 1 ******/
	TCanvas* c1 = new TCanvas("c1","Exercise3a");
	TH1F* h1 = new TH1F("h1","",100,0,10);
	TF1* f1 = new TF1("f1","gaus(0)",0,10);
	f1->SetParameter(0,1);
	f1->SetParameter(1,5);
	f1->SetParameter(2,1);

	h1->FillRandom("f1",5000);
	h1->Draw();
	std::cout << "Mean of histogram: " << h1->GetMean() << " +/- " << h1->GetMeanError() << std::endl;
	std::cout << "Std of histogram: " << h1->GetStdDev() << " +/- " << h1->GetStdDevError() << std::endl;

	/******* Save results ********/
	c1->SaveAs("Exercise3a.png");

	/*******************/
	/***** PART 2 ******/
	TCanvas* c2 = new TCanvas("c2","Exercise3b");
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
	c2->SaveAs("Exercise3b.png");

	/*****************************/
	TFile* outfile = new TFile("ex3.root", "RECREATE");
	f1->Write();
	h1->Write();
	f2->Write();
	h2->Write();
	f3->Write();
	h3->Write();
	outfile->Close();
	
}
