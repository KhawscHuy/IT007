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
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime),start(0),finish(0),final(0) {
        
    }
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void assignVariableGant(std::vector<Process>& p, int QT) {
    std::sort(p.begin(), p.end(), compareArrivalTime);

    std::queue<Process> processes;
    processes.push(p[0]);
    int startGant = p[0].arrivalTime;
    int endGant;
    std::vector<Process> CalculateWTandTAT;
    if (p[0].burstTime <= QT) {
        endGant = startGant + p[0].burstTime;
    }
    else {
        endGant = startGant + QT;
    }
    int i = 1;
    Process CurrentProcess(0, 0, 0);

    while (!processes.empty()) {
        CurrentProcess = processes.front();
        processes.pop();
        if (CurrentProcess.burstTime <= QT) {
            endGant = startGant + CurrentProcess.burstTime;
            CurrentProcess.burstTime = 0;
            CurrentProcess.final = true;
        }
        else {
            endGant = startGant + QT;
            CurrentProcess.burstTime -= QT;
            for (; i < p.size(); i++) {
                if (p[i].arrivalTime <= endGant)
                    processes.push(p[i]);
                else
                    break;
            }
            processes.push(CurrentProcess);
        }
        CurrentProcess.start = startGant;
        CurrentProcess.finish = endGant;
        CalculateWTandTAT.push_back(CurrentProcess);
        std::cout << "P[" << CurrentProcess.id << "]" << "\t|\t" << startGant << "\t|\t" << endGant << "\n";
        startGant = endGant;
    }
    float totWT = 0;
    float totTAT = 0;
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0;j<CalculateWTandTAT.size(); j++) {
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
    std::cout << "\nthời gian chờ trung bình: "<<totWT/p.size();
    std::cout << "\nthời gian hoàn thành trung bình: " << totTAT / p.size();
}

int main() {
    int n, QT;
    std::cout << "Nhập số tiến trình: ";
    std::cin >> n;
    std::cout << "Nhập số Quantum Time: ";
    std::cin >> QT;

    std::vector<Process> processes;

    for (int i = 0; i < n; i++) {
        int id, arrival, burst;
        std::cout << "Nhập ID, thời gian đến, thời gian chạy cho tiến trình " << i + 1 << ": ";
        std::cin >> id >> arrival >> burst;
        processes.emplace_back(id, arrival, burst);
    }

    std::cout << "ID\t|\tStart\tFinish\n";
    assignVariableGant(processes, QT);

    return 0;
}
