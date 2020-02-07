#include <iostream>
#include <fstream>
#include <sstream>
#include "TString.h"
#include "TH2D.h"

using namespace std;

void read_file(TString file_name, vector<double>& dat_temp, vector<double>& dat_humi)
{
    ifstream ifs;
    ifs.open(file_name);
    if (!ifs.is_open())
    {
        cerr << "could not open" << endl;
        return;
    }
    
//    vector<double> dat_temp;
//    vector<double> dat_humi;
    
    string line;
    getline(ifs,line); // read first line (and ignore)
    
    // loop over file
    while (getline(ifs,line))
    {
        std::stringstream ss;
        ss << line;
        
        std::getline(ss,line,','); // this weird time stamp
        
        getline(ss,line,',');
        dat_temp.push_back(std::stod(line));
        getline(ss,line,',');
        dat_humi.push_back(std::stod(line));
        
    }
    
    if (dat_temp.size()!=dat_humi.size())
    {
        cout << "Oops! Unequal amount of data in temperature and pressure columns. Aborting" << endl;
        return;
    }
}

void read_all_files(vector<double>& dat_temp, vector<double>& dat_humi)
{
    vector<string> in_names = {
            "01-Philipp_2020-02-06_01.csv",
            "01-Philipp_2020-02-07_01.csv",
            "02-Hallway_2020-02-06_01.csv",
            "02-Hallway_2020-02-07_01.csv",
            "03-Bathroom_2020-02-06_01.csv",
            "03-Bathroom_2020-02-07_01.csv"
    };
    
    for (auto& n : in_names)
    {
        read_file(n, dat_temp, dat_humi);
    }
}

void plot_temp_humi(TString file_name = "" /*vector<string> in_names = {}*/)
{

    vector<double> dat_temp;
    vector<double> dat_humi;
    
    if (file_name == "")
        read_all_files(dat_temp, dat_humi);
    else
        read_file(file_name, dat_temp, dat_humi);
    
    TH2D* h = new TH2D("hTempPres", "T-H-Diagram", 50, 15.0, 25.0, 100, 30.0, 70.0);
    h->GetXaxis()->SetTitle("temp in degC");
    h->GetYaxis()->SetTitle("humi in percent");
    
    for (size_t i=0; i<dat_temp.size(); i++)
    {
//        cout << "P: " << dat_humi.at(i) << "\tT: " << dat_temp.at(i) << endl;
        h->Fill(dat_temp.at(i), dat_humi.at(i));
    }
    
    h->Draw("colz");
}
