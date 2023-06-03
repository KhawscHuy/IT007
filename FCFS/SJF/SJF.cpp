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
    bool inWait;
public:
    Process(int processId, int arrival, int burst)
        : id(processId), arrivalTime(arrival), burstTime(burst), start(0), finish(0), tat(0), wt(0), inWait(false) {}
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
    bool getinWait() const {
        return inWait;
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
    void setinWait(bool inW) {
        inWait = inW;
    }
    friend bool operator>(Process P1, Process P2)
    {
        return (P1.burstTime > P2.burstTime);
    }
    friend bool operator<(Process P1, Process P2)
    {
        return (P1.burstTime < P2.burstTime);
    }
};
void setInWait(std::vector<Process> p, int pos) {
    for (int i = pos + 1; i < p.size(); i++) {
        if (p[i].getArrivalTime() < p[pos].getFinish()) {
            p[i].setinWait(1);
        }
    }
}
bool compareArrivalTimeAndBurstTime(const Process& a, const Process& b) {
    if (a.getArrivalTime() == b.getArrivalTime()) return a.getBurstTime() < b.getBurstTime();
    return a.getArrivalTime() < b.getArrivalTime();
}
bool compareBurstTime(const Process& a, const Process& b) {
        return a.getBurstTime() < b.getBurstTime();
}
void assignVariableGant(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), compareArrivalTimeAndBurstTime);
    int startGant;
    int endGant;
    int waitingtime = 0;
    for (int i = 0; i < processes.size(); i++) {
        setInWait(processes, i);
        if (i == 0) {
            startGant = processes[i].getArrivalTime() + waitingtime;
            endGant = startGant + processes[i].getBurstTime();
            processes[i].setStart(startGant);
            processes[i].setFinish(endGant);
            processes[i].setTurnaroundTime(endGant - processes[i].getArrivalTime());
            processes[i].setWaitingTime(processes[i].getArrivalTime() - startGant);
        }
        else {
            std::sort(processes.begin() + i, processes.end(), compareBurstTime);
            if (processes[i].getArrivalTime() >= processes[i - 1].getFinish())
                waitingtime = processes[i].getArrivalTime() - processes[i - 1].getFinish();
            startGant = processes[i - 1].getFinish() + waitingtime;
            endGant = startGant + processes[i].getBurstTime();
            processes[i].setStart(startGant);
            processes[i].setFinish(endGant);
            processes[i].setTurnaroundTime(endGant - processes[i].getArrivalTime());
            processes[i].setWaitingTime(startGant - processes[i].getArrivalTime());
        }
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
    float totwt = 0, tottat = 0;
    std::vector<Process> processes;

    for (int i = 0; i < n; i++) {
        int id, arrival, burst;
        std::cout << "Nhập ID, thời gian đến, thời gian chạy cho tiến trình " << i + 1 << ": ";
        std::cin >> id >> arrival >> burst;
        processes.emplace_back(id, arrival, burst);
    }
    assignVariableGant(processes);

    printProcessDetails(processes);
    for (int i = 0; i < n; i++) {
        totwt += processes[i].getWaitingTime();
        tottat += processes[i].getTurnaroundTime();
    }
    std::cout << "\nthời gian đợi trung bình là: " << totwt / n;
    std::cout << "\nthời gian chạy trung bình là: " << tottat / n;
    return 0;
}
