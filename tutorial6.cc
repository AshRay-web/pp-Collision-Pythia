#include <iostream>
#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"
#include "TThread.h"

// Function to handle the event generation and ROOT file creation
void *handel(void *ptr)
{
    int ith = (long)ptr;

    TFile *output = new TFile("common.root","recreate");

    TTree *tree = new TTree("tree", "tree");

    int id, event, size, no;
    double px, py, pz, m;

    tree->Branch("event", &event, "event/I");
    tree->Branch("size", &size, "size/I");
    tree->Branch("no", &no, "no/I");
    tree->Branch("id", &id, "id/I");
    tree->Branch("m", &m, "m/D");
    tree->Branch("px", &px, "px/D");
    tree->Branch("py", &py, "py/D");
    tree->Branch("pz", &pz, "pz/D");

    int nevents = 1e4;

    Pythia8::Pythia pythia;

    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 8.e3"); // 8 TeV
    pythia.readString("SoftQCD:all = on");
    pythia.readString("HardQCD:all = on");

    pythia.init();

    for (int i = 0; i < nevents; i++)
    {
        if (!pythia.next())
            continue;

        int entries = pythia.event.size();
        std::cout << "Event: " << i << std::endl;

        event = i;
        size = entries;

        for (int j = 0; j < entries; j++)
        {
            // Select only final-state particles
            if (!pythia.event[j].isFinal())
                continue;

            id = pythia.event[j].id();
            no = j;
            m = pythia.event[j].m();
            px = pythia.event[j].px();
            py = pythia.event[j].py();
            pz = pythia.event[j].pz();

            tree->Fill();
        }
    }

    output->Write();
    output->Close();

    return nullptr;
}

// Main function to initialize threads and run the handler
int main()
{
    const int numThreads = 4; // Number of threads to run
    TThread *threads[numThreads];

    // Create and start threads
    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = new TThread(Form("thread%d", i), handel, (void *)(long)i);
        threads[i]->Run();
    }

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; i++)
    {
        threads[i]->Join();
    }

    std::cout << "All threads completed successfully!" << std::endl;

    return 0;
}  
