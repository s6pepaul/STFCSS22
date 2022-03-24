#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"

void Exercise1(){
	
	/***** PART 1 ******/
	TCanvas* c1 = new TCanvas("c1","Exercise1a");
	TF1* f1 = new TF1("f1","pol1(0)",-10,10);
	f1->SetParameters(10,2);
	f1->Draw();
	
	/******* Save results ********/
	c1->SaveAs("Exercise1a.png");

	/*******************/
	/***** PART 2 ******/
	TCanvas* c2 = new TCanvas("c2","Exercise1b");
	c2->SetGrid();
	f1->Draw();
	TF1* f2 = new TF1("f2","pol2(0)",-10,10);
	f2->SetParameters(1,0.2,1);
	f2->SetLineColor(kBlue);
	f2->Draw("SAME");
	TF1* f3 = new TF1("f3","pol3(0)",-10,10);
	f3->SetParameters(1,-5,1.1,0.2);
	f3->SetLineColor(kGreen);
	f3->Draw("SAME");
	TF1* f4 = new TF1("f4","[0]*TMath::Sin(x+[1])+[2]",-10,10);
	f4->SetParameters(15,1,5);
	f4->SetLineColor(kOrange);
	f4->Draw("SAME");

	
	/******* Save results ********/
	c2->SaveAs("Exercise1b.png");

	/*****************************/
	TFile* outfile = new TFile("ex1.root", "RECREATE");
	f1->Write();
	f2->Write();
	f3->Write();
	f4->Write();
	outfile->Close();
	
}
