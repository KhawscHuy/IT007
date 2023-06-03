#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int start;
    int finish;
    bool final;

    Process(int id, int arrivalTime, int burstTime)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime), start(0), finish(0), final(false) {

    }
};
bool compareArrivalTimeAndBurstTime(const Process& a, const Process& b) {
    if (a.arrivalTime == b.arrivalTime) return a.burstTime < b.burstTime;
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process& a, const Process& b) {
    
        return a.burstTime < b.burstTime;
}
void assignVariableGant(std::vector<Process>& p) {
    std::sort(p.begin(), p.end(), compareArrivalTimeAndBurstTime);

    std::vector<Process> waiting;
    int startGant = p[0].arrivalTime;
    int endGant = startGant + p[0].burstTime;
    int i = 1;
    Process CurrentProcess=p[0];
    Process NextProcess(0,0,0);
    std::vector<Process> CalculateWTandTAT;
    while (!waiting.empty()||i!=p.size()) {
        for (; i < p.size(); i++) {
            if (p[i].arrivalTime <= endGant)
            {
                waiting.push_back(p[i]);
            }
            else break;
        }
        if (waiting.empty()) {
            CurrentProcess.final = 1;
            CurrentProcess.start = startGant;
            CurrentProcess.finish = endGant;
            CalculateWTandTAT.push_back(CurrentProcess);
            std::cout << "P[" << CurrentProcess.id << "]" << "\t|\t" << startGant << "\t|\t" << endGant << "\n";
            waiting.push_back(p[i]);
            
            CurrentProcess = p[i];
        }
        else {
            if (CurrentProcess.burstTime - waiting.front().arrivalTime > waiting.front().burstTime ) {
                endGant = waiting.front().arrivalTime;
                CurrentProcess.burstTime -= waiting.front().arrivalTime;
                waiting.push_back(CurrentProcess);
                CurrentProcess.start = startGant;
                CurrentProcess.finish = endGant;
                CalculateWTandTAT.push_back(CurrentProcess);
                std::cout << "P[" << CurrentProcess.id << "]" << "\t|\t" << startGant << "\t|\t" << endGant << "\n";
            }
            else {
                CurrentProcess.final = 1;
                CurrentProcess.start = startGant;
                CurrentProcess.finish = endGant;
                CalculateWTandTAT.push_back(CurrentProcess);
                std::cout << "P[" << CurrentProcess.id << "]" << "\t|\t" << startGant << "\t|\t" << endGant << "\n";
            }
            CurrentProcess = waiting.front();
            waiting.erase(waiting.begin());
            std::sort(waiting.begin(), waiting.end(), compareBurstTime);
            startGant = endGant;
            endGant = startGant + CurrentProcess.burstTime;
        }
    }
    CurrentProcess.final = 1;
    CurrentProcess.start = startGant;
    CurrentProcess.finish = endGant;
    CalculateWTandTAT.push_back(CurrentProcess);
    std::cout << "P[" << CurrentProcess.id << "]" << "\t|\t" << startGant << "\t|\t" << endGant << "\n";
    float totWT = 0;
    float totTAT = 0;
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < CalculateWTandTAT.size(); j++) {
            if (CalculateWTandTAT[j].id != p[i].id) {
                totWT += CalculateWTandTAT[j].finish - CalculateWTandTAT[j].start;
            }
            if (CalculateWTandTAT[j].final == true && (CalculateWTandTAT[j].id == p[i].id)) {
                totTAT += CalculateWTandTAT[j].finish - p[i].arrivalTime;
                break;
            }
        }
        totWT -= p[i].arrivalTime;
    }
    std::cout << "\nthời gian chờ trung bình: " << totWT / p.size();
    std::cout << "\nthời gian hoàn thành trung bình: " << totTAT / p.size();
}

int main() {
    int n;
    std::cout << "Nhập số tiến trình: ";
    std::cin >> n;

    std::vector<Process> processes;

    for (int i = 0; i < n; i++) {
        int id, arrival, burst;
        std::cout << "Nhập ID, thời gian đến, thời gian chạy cho tiến trình " << i + 1 << ": ";
        std::cin >> id >> arrival >> burst;
        processes.emplace_back(id, arrival, burst);
    }

    std::cout << "ID\t|\tStart\tFinish\n";
    assignVariableGant(processes);

    return 0;
}
