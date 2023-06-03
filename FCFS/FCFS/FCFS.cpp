#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class Process {
private:
    int id;
    int arrivalTime;
    int burstTime;
    int start;
    int finish;
    int tat;
    int wt;

public:
    Process(int processId, int arrival, int burst)
        : id(processId), arrivalTime(arrival), burstTime(burst), start(0), finish(0), tat(0), wt(0) {}

    int getID() const {
        return id;
    }

    int getArrivalTime() const {
        return arrivalTime;
    }

    int getBurstTime() const {
        return burstTime;
    }

    int getStart() const {
        return start;
    }

    int getFinish() const {
        return finish;
    }

    int getTurnaroundTime() const {
        return tat;
    }

    int getWaitingTime() const {
        return wt;
    }

    void setID(int processId) {
        id = processId;
    }

    void setArrivalTime(int arrival) {
        arrivalTime = arrival;
    }

    void setBurstTime(int burst) {
        burstTime = burst;
    }

    void setStart(int startTime) {
        start = startTime;
    }

    void setFinish(int finishTime) {
        finish = finishTime;
    }

    void setTurnaroundTime(int turnaround) {
        tat = turnaround;
    }

    void setWaitingTime(int waiting) {
        wt = waiting;
    }
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.getArrivalTime() < b.getArrivalTime();
}

void calculateMetrics(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = processes[0].getArrivalTime();

    for (int i = 0; i < n; i++) {
        processes[i].setStart(std::max(currentTime, processes[i].getArrivalTime()));
        currentTime = processes[i].getStart() + processes[i].getBurstTime();
        processes[i].setFinish(currentTime);
        processes[i].setTurnaroundTime(processes[i].getFinish() - processes[i].getArrivalTime());
        processes[i].setWaitingTime(processes[i].getTurnaroundTime() - processes[i].getBurstTime());
    }
}

void printProcessDetails(const std::vector<Process>& processes) {
    std::cout << "ID\tArrival\tBurst\tStart\tTurnaround\tFinish\n";
    for (const Process& p : processes) {
        std::cout << p.getID() << "\t" << p.getArrivalTime() << "\t" << p.getBurstTime()
            << "\t" << p.getStart() << "\t" << p.getTurnaroundTime() << "\t\t" << p.getFinish() << "\n";
    }
}

int main() {
    int n;
    std::cout << "Nhập số tiến trình: ";
    std::cin >> n;
    float totwt = 0 , tottat = 0;
    std::vector<Process> processes;

    for (int i = 0; i < n; i++) {
        int id, arrival, burst;
        std::cout << "Nhập ID, thời gian đến, thời gian chạy cho tiến trình " << i + 1 << ": ";
        std::cin >> id >> arrival >> burst;
        processes.emplace_back(id, arrival, burst);
    }

    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    calculateMetrics(processes);

    printProcessDetails(processes);
    for (int i = 0; i < n; i++) {
        totwt += processes[i].getWaitingTime();
        tottat += processes[i].getTurnaroundTime();
    }
    std::cout << "\nthời gian đợi trung bình là: " << totwt/n;
    std::cout << "\nthời gian chạy trung bình là: "<< tottat/n;
    return 0;
}
