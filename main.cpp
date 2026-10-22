
#include <iostream>
using namespace std;

const int MAX = 50;

bool present(int f[], int c, int p) {
    for (int i = 0; i < c; i++)
        if (f[i] == p) return true;
    return false;
}

int emptySlot(int f[], int c) {
    for (int i = 0; i < c; i++)
        if (f[i] == -1) return i;
    return -1;
}

void show(int f[], int c) {
    for (int i = 0; i < c; i++) {
        if (f[i] == -1)
            cout << "- ";
        else
            cout << f[i] << " ";
    }
}

int FIFO(int p[], int n, int c) {
    int f[10], next = 0, faults = 0;

    for (int i = 0; i < c; i++)
        f[i] = -1;

    cout << "\nFIFO\nPage\tFrames\t\tStatus\n";

    for (int i = 0; i < n; i++) {
        bool hit = present(f, c, p[i]);

        if (!hit) {
            faults++;
            f[next] = p[i];
            next = (next + 1) % c;
        }

        cout << p[i] << "\t";
        show(f, c);
        cout << "\t" << (hit ? "Hit" : "Fault") << "\n";
    }

    cout << "Total page faults = " << faults << "\n";
    return faults;
}

int LRU(int p[], int n, int c) {
    int f[10], used[10], faults = 0;

    for (int i = 0; i < c; i++) {
        f[i] = -1;
        used[i] = -1;
    }

    cout << "\nLRU\nPage\tFrames\t\tStatus\n";

    for (int i = 0; i < n; i++) {
        int slot = -1;

        for (int j = 0; j < c; j++)
            if (f[j] == p[i])
                slot = j;

        bool hit = (slot != -1);

        if (!hit) {
            faults++;
            slot = emptySlot(f, c);

            if (slot == -1) {
                slot = 0;

                for (int j = 1; j < c; j++)
                    if (used[j] < used[slot])
                        slot = j;
            }

            f[slot] = p[i];
        }

        used[slot] = i;

        cout << p[i] << "\t";
        show(f, c);
        cout << "\t" << (hit ? "Hit" : "Fault") << "\n";
    }

    cout << "Total page faults = " << faults << "\n";
    return faults;
}

int Optimal(int p[], int n, int c) {
    int f[10], faults = 0;

    for (int i = 0; i < c; i++)
        f[i] = -1;

    cout << "\nOptimal\nPage\tFrames\t\tStatus\n";

    for (int i = 0; i < n; i++) {
        bool hit = present(f, c, p[i]);

        if (!hit) {
            faults++;
            int slot = emptySlot(f, c);

            if (slot == -1) {
                int farthest = -1;
                slot = 0;

                for (int j = 0; j < c; j++) {
                    int nextUse = n + 1;

                    for (int k = i + 1; k < n; k++) {
                        if (p[k] == f[j]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        slot = j;
                    }
                }
            }

            f[slot] = p[i];
        }

        cout << p[i] << "\t";
        show(f, c);
        cout << "\t" << (hit ? "Hit" : "Fault") << "\n";
    }

    cout << "Total page faults = " << faults << "\n";
    return faults;
}

int main() {
    int pages[MAX], n, c;

    cout << "PAGE REPLACEMENT SIMULATOR\n";

    cout << "Enter number of page references (1-50): ";
    cin >> n;

    if (n < 1 || n > MAX) {
        cout << "Invalid input.\n";
        return 1;
    }

    cout << "Enter page numbers separated by spaces: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames (1-10): ";
    cin >> c;

    if (c < 1 || c > 10) {
        cout << "Invalid input.\n";
        return 1;
    }

    int a = FIFO(pages, n, c);
    int b = LRU(pages, n, c);
    int d = Optimal(pages, n, c);

    cout << "\nCOMPARISON\n";
    cout << "FIFO faults: " << a << "\n";
    cout << "LRU faults: " << b << "\n";
    cout << "Optimal faults: " << d << "\n";

    cout << "Optimal is a theoretical benchmark because "
         << "it uses future references.\n";

    return 0;
}