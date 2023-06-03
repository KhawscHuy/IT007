
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

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

    Process& operator=(const Process& other) {
        id = other.id;
        arrivalTime = other.arrivalTime;
        burstTime = other.burstTime;
        start = other.start;
        finish = other.finish;
        tat = other.tat;
        wt = other.wt;
        return *this;
    }

    friend istream& operator>>(std::istream& in, Process& p) {
        in >> p.id >> p.arrivalTime >> p.burstTime;
        return in;
    }
};
queue<Process> Sort_Queue(queue<Process>& q)
{
    vector<Process> temp;
    while (!q.empty())
    {
        temp.push_back(q.front());
        q.pop();
    }
    sort(temp.begin(), temp.end(), [](const Process& a, const Process& b) {
        return a.getBurstTime() < b.getBurstTime();
    });

    for (int i = 0; i < temp.size(); i++)
    {
        q.push(temp.back());
    }
    return q;
}
struct CompareProcessArrival {
    bool operator()(const Process& a, const Process& b) {
        return a.getArrivalTime() > b.getArrivalTime();
    }
};

int main() {
    int n;
    std::cout << "Mời nhập số tiến trình: ";
    cin >> n;


    vector<Process> processes;
    queue<Process> waitingQueue;
    Process currentProcess(0, 0, 0);
    Process nextProcess(0, 0, 0);

    for (int i = 0; i < n; i++) {
        cin >> currentProcess;
        processes.push_back(currentProcess);
    }
    float totwt = 0, tottat = 0;


    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });


    currentProcess = processes[0];
    int startGant = currentProcess.getArrivalTime();
    int endGant = currentProcess.getBurstTime();
    int currentProcessIdentify = 0;
    int waitingTime = 0;
    int i = 1;
    for (; startGant <= endGant; startGant++) {
        processes[currentProcessIdentify].setStart(startGant+waitingTime);
        processes[currentProcessIdentify].setFinish(endGant);
        
        while (true) {
            if (processes[i].getArrivalTime() < endGant) {
                waitingQueue.push(processes[i++]);
            }
            else 
            {
                waitingTime = processes[i].getArrivalTime() - endGant;
                break;
            }
        }
        if(waitingQueue.empty()!=1) waitingQueue = Sort_Queue(waitingQueue);
        if (startGant == endGant) {
            if (waitingQueue.empty() != 1&& i!=n) {
                nextProcess = waitingQueue.front();
                waitingQueue.pop();
                currentProcess = nextProcess;
                endGant = startGant + currentProcess.getBurstTime();
                startGant--;
                currentProcessIdentify++;
            }
            else if (waitingQueue.empty() == 1 ) {//tiến trình chưa vào WaitingQueue
                currentProcess = processes[i];
                endGant = startGant + currentProcess.getBurstTime()+waitingTime;
                startGant--;
                currentProcessIdentify++;
            }
            if (currentProcessIdentify == n)
            {
                break;
            }
        }
    }

    for ( i = 0; i < n; i++) {
        processes[i].setWaitingTime(processes[i].getStart() - processes[i].getArrivalTime());
        processes[i].setTurnaroundTime(processes[i].getFinish() - processes[i].getArrivalTime()) ;
    }

    std::cout << "\nPName\tArrtime\tBurtime\tStart\tTAT\tFinish\n";
    for ( i = 0; i < n; ++i) {
        std::cout << processes[i].getID() << "\t" << processes[i].getArrivalTime() << "\t" << processes[i].getBurstTime()
            << "\t" << processes[i].getStart() << "\t" << processes[i].getTurnaroundTime() << "\t" << processes[i].getFinish() << endl;
        totwt += processes[i].getWaitingTime();
        tottat += processes[i].getTurnaroundTime();
    }
    std::cout << "\navarage waiting time : " << totwt / n;
    std::cout << "\navarage tat: " << tottat / n;
    std::cout << "\n";

    return 0;
}
