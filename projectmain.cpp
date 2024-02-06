#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Function to schedule jobs to threads
vector<pair<int, long>> scheduleJobs(int n, int m, vector<long> &processingTimesOfJobs) {
// Initialize threadAvalability and jobStartTimes to track thread availability and job 
// start times
vector<long> threadAvailability(n, 0);
//int = thread job is assigned to, long = time job starts
vector<pair<int, long>> jobStartTimes;
for (int i = 0; i < m; ++i) {
  // Find the thread with the earliest minimum availability
  int minAvailabilityThread = 0;
  for (int j = 1; j < n; ++j) {
    if (threadAvailability[j] < threadAvailability[minAvailabilityThread]) {
        minAvailabilityThread = j;
      }
    }
    // Calculate start time for current job on selected thread
    long startTime = max(threadAvailability[minAvailabilityThread],
            jobStartTimes.empty() ? 0 : jobStartTimes.back().second);
    // Change thread availability for current thread
    threadAvailability[minAvailabilityThread] = startTime + processingTimesOfJobs[i];

  // Insert results to the output list
  jobStartTimes.push_back({minAvailabilityThread, startTime});
  }
  return jobStartTimes;
}

int main() {
  // Open input file
  ifstream inputFile("input2.txt");
  // Check if the file is opened successfully
  if (!inputFile) {
    cerr << "Cannot open input file." << endl;
    return 1;
  }
  // Read the input from imported file
  
  int n; //number of threads
  int m; //number of jobs

  inputFile >> n >> m;

  vector<long> processingTimesOfJobs(m);

  for (int i = 0; i < m; ++i) { //appends each processing time to array
    inputFile >> processingTimesOfJobs[i];
  }
  // Close the input file
  inputFile.close();

  // Call the scheduledJobs function
  vector<pair<int, long>> scheduledJobs = scheduleJobs(n, m, processingTimesOfJobs);

  // Open output file
  ofstream outputFile("output2.txt");

  // Make sure the file is opened without errors
  if (!outputFile) {
    cerr << "Error opening output file." << endl;
    return 1;
  }

  // Print the results to the output file
  for (const auto &job : scheduledJobs) {
    outputFile << job.first << " " << job.second << endl;
  }

  // Close the output file
  outputFile.close();

  return 0;
}
