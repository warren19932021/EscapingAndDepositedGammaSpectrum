void Real_Angular_Polar_Draw() {


   gStyle->SetLabelSize(0.06,"xyz");
   gStyle->SetLabelOffset(0.012,"xy");
   gStyle->SetTitleOffset(1.05,"x");
   gStyle->SetTitleOffset(1.15,"y");
   gStyle->SetTitleSize(0.065,"xy");
   gStyle->SetTitleBorderSize(0);
   gStyle->SetOptStat("");

   //double thMax =1.5;
   //auto hPol = new TH2D("hPol", "",  180,-TMath::Pi(),TMath::Pi(),  90,0,thMax  );
   auto hPol = new TH2D("hPol", "",  180, 0 ,2*(TMath::Pi()),  90,0, TMath::Pi()  );

   hPol->GetZaxis()->SetMaxDigits(3);

   auto cv = new TCanvas();



   TFile *_file0 = TFile::Open("TESTTEST0.root"); // gps
   TTree * hahaha = (TTree*)_file0->FindObjectAny("Ntuple;1");

   cout<<"Number of Entries: "<<hahaha->GetEntries()<<endl;

   double Theta = 10;
   double phi = 10;
   hahaha->SetBranchAddress("Theta", &Theta);
   hahaha->SetBranchAddress("phi", &phi);

      //for (int i=0; i<100;i++)
   for (int i=0; i<hahaha->GetEntries();i++)
   {
     hahaha->GetEntry(i);
     if(phi!=10) hPol->Fill(phi,Theta);
     //if(fPhi!=10) hPol->Fill(fPhi,fTheta-1.570796);
   }



   hPol->Draw("lego2 polz");

   hPol->SetLineColorAlpha(kBlack, 0.0);
   cv->SetRightMargin(0.15);
   cv->SetTheta(90.);
   cv->SetPhi(0.);
   gPad->Update();

   auto PPad = new TPad("p","p",0.01,0.,.94,1.);
   PPad->SetFillStyle(4000);
   PPad->Draw();
   PPad->cd();

   //auto gp = new TGraphPolargram("g",0,thMax, -180., 180.);
   auto gp = new TGraphPolargram("g",0,TMath::Pi(), -180., 180.);
   gp->SetToDegree ();
   gp->SetNdivPolar(8);
   gp->SetNdivRadial(4);
   gp->SetLineColor(1);
   gp->Draw();


}
