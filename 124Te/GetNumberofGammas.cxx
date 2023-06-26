
void GetNumberofGammas(){



                  TFile * _file0 = TFile::Open("TEST0.root","read");
                  TFile * _file1 = TFile::Open("TEST1.root","read");
                  TFile * _file2 = TFile::Open("TEST2.root","read");
                  TFile * _file3 = TFile::Open("TEST3.root","read");
                  TFile * _file4 = TFile::Open("TEST4.root","read");
                  TFile * _file5 = TFile::Open("TEST5.root","read");
                  TFile * _file6 = TFile::Open("TEST6.root","read");
                  TFile * _file7 = TFile::Open("TEST7.root","read");
                  TFile * _file8 = TFile::Open("TEST8.root","read");
                  TFile * _file9 = TFile::Open("TEST9.root","read");
                  TFile * _file10 = TFile::Open("TEST10.root","read");
                  TFile * _file11 = TFile::Open("TEST11.root","read");
                  TFile * _file12 = TFile::Open("TEST12.root","read");
                  TFile * _file13 = TFile::Open("TEST13.root","read");
                  TFile * _file14 = TFile::Open("TEST14.root","read");
                  TFile * _file15 = TFile::Open("TEST15.root","read");
                  TFile * _file16 = TFile::Open("TEST16.root","read");
                  TFile * _file17 = TFile::Open("TEST17.root","read");
                  TFile * _file18 = TFile::Open("TEST18.root","read");
                  TFile * _file19 = TFile::Open("TEST19.root","read");
                  TFile * _file20 = TFile::Open("TEST20.root","read");
                  TFile * _file21 = TFile::Open("TEST21.root","read");
                  TFile * _file22 = TFile::Open("TEST22.root","read");
                  TFile * _file23 = TFile::Open("TEST23.root","read");
                  TFile * _file24 = TFile::Open("TEST24.root","read");
                  TFile * _file25 = TFile::Open("TEST25.root","read");
                  TFile * _file26 = TFile::Open("TEST26.root","read");
                  TFile * _file27 = TFile::Open("TEST27.root","read");
                  TFile * _file28 = TFile::Open("TEST28.root","read");
                  TFile * _file29 = TFile::Open("TEST29.root","read");
                  TFile * _file30 = TFile::Open("TEST30.root","read");
                  TFile * _file31 = TFile::Open("TEST31.root","read");
                  TFile * _file32 = TFile::Open("TEST32.root","read");
                  TFile * _file33 = TFile::Open("TEST33.root","read");
                  TFile * _file34 = TFile::Open("TEST34.root","read");
                  TFile * _file35 = TFile::Open("TEST35.root","read");
                  TFile * _file36 = TFile::Open("TEST36.root","read");
                  TFile * _file37 = TFile::Open("TEST37.root","read");
                  TFile * _file38 = TFile::Open("TEST38.root","read");
                  TFile * _file39 = TFile::Open("TEST39.root","read");






                  TTree* tree0 =  (TTree*) _file0->FindObjectAny("EGammaSignal;1");   
                  TTree* tree1 =  (TTree*) _file1->FindObjectAny("EGammaSignal;1");
                  TTree* tree2 =  (TTree*) _file2->FindObjectAny("EGammaSignal;1");
                  TTree* tree3 =  (TTree*) _file3->FindObjectAny("EGammaSignal;1");
                  TTree* tree4 =  (TTree*) _file4->FindObjectAny("EGammaSignal;1");
                  TTree* tree5 =  (TTree*) _file5->FindObjectAny("EGammaSignal;1");
                  TTree* tree6 =  (TTree*) _file6->FindObjectAny("EGammaSignal;1");
                  TTree* tree7 =  (TTree*) _file7->FindObjectAny("EGammaSignal;1");
                  TTree* tree8 =  (TTree*) _file8->FindObjectAny("EGammaSignal;1");
                  TTree* tree9 =  (TTree*) _file9->FindObjectAny("EGammaSignal;1");
                  TTree* tree10 = (TTree*) _file10->FindObjectAny("EGammaSignal;1");
                  TTree* tree11 = (TTree*) _file11->FindObjectAny("EGammaSignal;1");
                  TTree* tree12 = (TTree*) _file12->FindObjectAny("EGammaSignal;1");
                  TTree* tree13 = (TTree*) _file13->FindObjectAny("EGammaSignal;1");
                  TTree* tree14 = (TTree*) _file14->FindObjectAny("EGammaSignal;1");
                  TTree* tree15 = (TTree*) _file15->FindObjectAny("EGammaSignal;1");
                  TTree* tree16 = (TTree*) _file16->FindObjectAny("EGammaSignal;1");
                  TTree* tree17 = (TTree*) _file17->FindObjectAny("EGammaSignal;1");
                  TTree* tree18 = (TTree*) _file18->FindObjectAny("EGammaSignal;1");
                  TTree* tree19 = (TTree*) _file19->FindObjectAny("EGammaSignal;1");
                  TTree* tree20 = (TTree*) _file20->FindObjectAny("EGammaSignal;1");
                  TTree* tree21 = (TTree*) _file21->FindObjectAny("EGammaSignal;1");
                  TTree* tree22 = (TTree*) _file22->FindObjectAny("EGammaSignal;1");
                  TTree* tree23 = (TTree*) _file23->FindObjectAny("EGammaSignal;1");
                  TTree* tree24 = (TTree*) _file24->FindObjectAny("EGammaSignal;1");
                  TTree* tree25 = (TTree*) _file25->FindObjectAny("EGammaSignal;1");
                  TTree* tree26 = (TTree*) _file26->FindObjectAny("EGammaSignal;1");
                  TTree* tree27 = (TTree*) _file27->FindObjectAny("EGammaSignal;1");
                  TTree* tree28 = (TTree*) _file28->FindObjectAny("EGammaSignal;1");
                  TTree* tree29 = (TTree*) _file29->FindObjectAny("EGammaSignal;1");
                  TTree* tree30 = (TTree*) _file30->FindObjectAny("EGammaSignal;1");
                  TTree* tree31 = (TTree*) _file31->FindObjectAny("EGammaSignal;1");
                  TTree* tree32 = (TTree*) _file32->FindObjectAny("EGammaSignal;1");
                  TTree* tree33 = (TTree*) _file33->FindObjectAny("EGammaSignal;1");
                  TTree* tree34 = (TTree*) _file34->FindObjectAny("EGammaSignal;1");
                  TTree* tree35 = (TTree*) _file35->FindObjectAny("EGammaSignal;1");
                  TTree* tree36 = (TTree*) _file36->FindObjectAny("EGammaSignal;1");
                  TTree* tree37 = (TTree*) _file37->FindObjectAny("EGammaSignal;1");
                  TTree* tree38 = (TTree*) _file38->FindObjectAny("EGammaSignal;1");
                  TTree* tree39 = (TTree*) _file39->FindObjectAny("EGammaSignal;1");



                  cout<< tree0->GetEntries()<<endl;    
                  cout<< tree1->GetEntries()<<endl; 
                  cout<< tree2->GetEntries()<<endl; 
                  cout<< tree3->GetEntries()<<endl; 
                  cout<< tree4->GetEntries()<<endl; 
                  cout<< tree5->GetEntries()<<endl; 
                  cout<< tree6->GetEntries()<<endl; 
                  cout<< tree7->GetEntries()<<endl; 
                  cout<< tree8->GetEntries()<<endl; 
                  cout<< tree9->GetEntries()<<endl; 
                  cout<< tree10->GetEntries()<<endl; 
                  cout<< tree11->GetEntries()<<endl; 
                  cout<< tree12->GetEntries()<<endl; 
                  cout<< tree13->GetEntries()<<endl; 
                  cout<< tree14->GetEntries()<<endl; 
                  cout<< tree15->GetEntries()<<endl; 
                  cout<< tree16->GetEntries()<<endl; 
                  cout<< tree17->GetEntries()<<endl; 
                  cout<< tree18->GetEntries()<<endl; 
                  cout<< tree19->GetEntries()<<endl; 
                  cout<< tree20->GetEntries()<<endl; 
                  cout<< tree21->GetEntries()<<endl; 
                  cout<< tree22->GetEntries()<<endl; 
                  cout<< tree23->GetEntries()<<endl; 
                  cout<< tree24->GetEntries()<<endl; 
                  cout<< tree25->GetEntries()<<endl; 
                  cout<< tree26->GetEntries()<<endl; 
                  cout<< tree27->GetEntries()<<endl; 
                  cout<< tree28->GetEntries()<<endl; 
                  cout<< tree29->GetEntries()<<endl; 
                  cout<< tree30->GetEntries()<<endl; 
                  cout<< tree31->GetEntries()<<endl; 
                  cout<< tree32->GetEntries()<<endl; 
                  cout<< tree33->GetEntries()<<endl; 
                  cout<< tree34->GetEntries()<<endl; 
                  cout<< tree35->GetEntries()<<endl; 
                  cout<< tree36->GetEntries()<<endl; 
                  cout<< tree37->GetEntries()<<endl; 
                  cout<< tree38->GetEntries()<<endl; 
                  cout<< tree39->GetEntries()<<endl; 





}
