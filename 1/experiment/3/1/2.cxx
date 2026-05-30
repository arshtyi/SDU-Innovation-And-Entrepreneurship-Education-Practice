#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define F(T, i, a, b) for (T i = (a); i < (b); ++i)
#define FF(T, i, a, b) for (T i = (a); i <= (b); ++i)
#define R(T, i, a, b) for (T i = (a); i > (b); --i)
#define RR(T, i, a, b) for (T i = (a); i >= (b); --i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define allab(x, a, b) (x).begin() + (a), (x).begin() + (b)
#define rallab(x, a, b) (x).rbegin() + (a), (x).rbegin() + (b)
#define pb push_back
#define eb emplace_back
#define pf push_front
#define ef emplace_front
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const int M1 = 1e9 + 7, M2 = 998244353;
#define endl '\n'
#define local freopen("data.in", "r", stdin)
#define locall freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
// #define int ll
static unsigned int p = 1;
int myrand() {
    p = p * 1103515245 + 12345;
    return (unsigned int)(p / 65536) % 100;
}
struct Task {
    string name;
    ll duration;
    int order;
};
vector<Task> tasks;
struct Workshop {
    string name;
    string mode;
    bool busy = false;
    deque<int> fifo;
    priority_queue<int, vector<int>, function<bool(int, int)>> pq;
    Workshop()
        : pq([](int, int) { return false; }) {}
    Workshop(string name, string mode, function<bool(int, int)> cmp)
        : name(std::move(name))
        , mode(std::move(mode))
        , pq(std::move(cmp)) {}
    bool empty() const {
        return mode == "TF" ? fifo.empty() : pq.empty();
    }
    void push(int task_id) {
        if (mode == "TF")
            fifo.push_back(task_id);
        else
            pq.push(task_id);
    }
    int pop() {
        if (mode == "TF") {
            int task_id = fifo.front();
            fifo.pop_front();
            return task_id;
        }
        int task_id = pq.top();
        pq.pop();
        return task_id;
    }
};
struct Event {
    ll finish_time;
    int order;
    int task_id;
    int workshop_id;
};
struct EventCmp {
    bool operator()(const Event& a, const Event& b) const {
        if (a.finish_time != b.finish_time)
            return a.finish_time > b.finish_time;
        return a.order > b.order;
    }
};
void _() {
    int n, m;
    cin >> n >> m;
    vector<Workshop> workshops;
    workshops.reserve(n);
    unordered_map<string, int> id;
    F(int, i, 0, n) {
        string name, mode;
        cin >> name >> mode;
        function<bool(int, int)> cmp;
        if (mode == "SF") {
            cmp = [](int a, int b) {
                if (tasks[a].duration != tasks[b].duration)
                    return tasks[a].duration > tasks[b].duration;
                return tasks[a].name < tasks[b].name;
            };
        } else {
            cmp = [](int a, int b) {
                if (tasks[a].duration != tasks[b].duration)
                    return tasks[a].duration < tasks[b].duration;
                return tasks[a].name < tasks[b].name;
            };
        }
        id[name] = i;
        workshops.emplace_back(name, mode, cmp);
    }
    priority_queue<Event, vector<Event>, EventCmp> events;
    auto start_task = [&](int workshop_id, int task_id, ll now) {
        workshops[workshop_id].busy = true;
        events.push({now + tasks[task_id].duration, tasks[task_id].order, task_id, workshop_id});
    };
    auto finish_until = [&](ll current_time) {
        while (!events.empty() && events.top().finish_time <= current_time) {
            Event event = events.top();
            events.pop();
            Workshop& workshop = workshops[event.workshop_id];
            cout << event.finish_time << ' ' << tasks[event.task_id].name << endl;
            if (workshop.empty()) {
                workshop.busy = false;
            } else {
                int next_task = workshop.pop();
                start_task(event.workshop_id, next_task, event.finish_time);
            }
        }
    };
    tasks.reserve(m);
    F(int, order, 0, m) {
        ll t, d;
        int k;
        string s;
        cin >> t >> s >> d >> k;
        vector<int> possible(k);
        F(int, i, 0, k) {
            string name;
            cin >> name;
            possible[i] = id[name];
        }
        finish_until(t);
        int probability = 100 / k;
        int workshop_id = possible.back();
        F(int, i, 0, k - 1) {
            if (probability > myrand()) {
                workshop_id = possible[i];
                break;
            }
        }
        int task_id = (int)tasks.size();
        tasks.push_back({s, d, order});
        if (workshops[workshop_id].busy)
            workshops[workshop_id].push(task_id);
        else
            start_task(workshop_id, task_id, t);
    }
    finish_until(LLINF);
}
signed main() {
    // local;
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _();
    return 0;
}
