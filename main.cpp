#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
#include <limits.h>
using namespace std;

class Metro_Graph
{
public:
    class Vertex
    {
    public:
        unordered_map<string, int> neighbours;
    };

    static unordered_map<string, Vertex> vertices;

    Metro_Graph()
    {
        vertices.clear(); 
    }

    int numVetex()
    {
        return vertices.size();
    }

    bool CheckIfContainsVertex(string vname)
    {
        return vertices.count(vname) > 0;
    }

    void addStation(string vname)
    {
        Vertex vtx;
        vertices[vname] = vtx;
    }

    void removeStation(string vname)
    {
        Vertex vtx = vertices[vname];
        vector<string> keys;
        for (auto it = vtx.neighbours.begin(); it != vtx.neighbours.end(); it++)
        {
            keys.push_back(it->first);
        }

        for (string key : keys)
        {
            Vertex neighbourVertex = vertices[key];
            neighbourVertex.neighbours.erase(vname);
        }

        vertices.erase(vname);
    }

    int numEdges()
    {
        int count = 0;
        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            Vertex vtx = it->second;
            count += vtx.neighbours.size();
        }

        return count / 2;
    }

    bool containsEdge(string vname1, string vname2)
    {
        if (vertices.count(vname1) == 0 || vertices.count(vname2) == 0 || vertices[vname1].neighbours.count(vname2) == 0)
        {
            return false;
        }

        return true;
    }

    void addEdge(string vname1, string vname2, int value)
    {
        if (vertices.count(vname1) == 0 || vertices.count(vname2) == 0 || vertices[vname1].neighbours.count(vname2) > 0)
        {
            return;
        }

        vertices[vname1].neighbours[vname2] = value;
        vertices[vname2].neighbours[vname1] = value;
    }

    void removeEdge(string vname1, string vname2)
    {
        if (vertices.count(vname1) == 0 || vertices.count(vname2) == 0 || vertices[vname1].neighbours.count(vname2) == 0)
        {
            return;
        }

        vertices[vname1].neighbours.erase(vname2);
        vertices[vname2].neighbours.erase(vname1);
    }

    void display_Map()
    {
        cout << "\t MAP OF DELHI METRO" << endl;
        cout << "\t------------------" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << endl;
        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            string key = it->first;
            string str = key + " =>" + "\n";
            Vertex vtx = it->second;
            for (auto it2 = vtx.neighbours.begin(); it2 != vtx.neighbours.end(); it2++)
            {
                string nbr = it2->first;
                str += "\t" + nbr + "\t";
                if (nbr.length() < 16)
                    str += "\t";
                if (nbr.length() < 8)
                    str += "\t";
                str += to_string(it2->second) + "\n";
            }
            cout << str << endl;
        }
        cout << "\t------------------" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << endl;
    }

    void display_Stations()
    {
        cout << endl;
        cout << "***********************************************************************" << endl;
        int i = 1;
        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            string key = it->first;
            cout << i << ". " << key << endl;
            i++;
        }
        cout << "***********************************************************************" << endl;
        cout << endl;
    }

    bool checkPath(string vname1, string vname2, unordered_map<string, bool> &processed)
    {
        if (containsEdge(vname1, vname2))
        {
            return true;
        }

        processed[vname1] = true;

        Vertex vtx = vertices[vname1];
        for (auto it = vtx.neighbours.begin(); it != vtx.neighbours.end(); it++)
        {
            string nbr = it->first;
            if (!processed.count(nbr))
            {
                if (checkPath(nbr, vname2, processed))
                {
                    return true;
                }
            }
        }

        return false;
    }

    class DijkstraPair
    {
    public:
        string vname;
        string PathSoFar; 
        int cost;

        bool operator<(const DijkstraPair &other) const
        {
            return cost > other.cost;
        }
    };

    int dijkstra(string source, string des, bool nan)
    {
        int val = 0;
        vector<string> ans;
        unordered_map<string, DijkstraPair> map;

        priority_queue<DijkstraPair> pq;

        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            string key = it->first;
            DijkstraPair np;
            np.vname = key;
            np.cost = INT_MAX;

            if (key == source)
            {
                np.cost = 0;
                np.PathSoFar = key;
            }

            pq.push(np);
            map[key] = np;
        }

        while (!pq.empty())
        {
            DijkstraPair rp = pq.top();
            pq.pop();

            if (rp.vname == des)
            {
                val = rp.cost;
                break;
            }

            map.erase(rp.vname);

            ans.push_back(rp.vname);

            Vertex v = vertices[rp.vname];
            for (auto it = v.neighbours.begin(); it != v.neighbours.end(); it++)
            {
                string nbr = it->first;
                if (map.count(nbr))
                {
                    int oc = map[nbr].cost;
                    Vertex k = vertices[rp.vname];
                    int nc;
                    if (nan)
                        nc = rp.cost + 120 + 40 * k.neighbours[nbr];
                    else
                        nc = rp.cost + k.neighbours[nbr];

                    if (nc < oc)
                    {
                        DijkstraPair gp = map[nbr];
                        gp.PathSoFar = rp.PathSoFar + nbr;
                        gp.cost = nc;

                        pq.push(gp);
                    }
                }
            }
        }
        return val;
    }

    class Pair
    {
    public:
        string vname;
        string PathSoFar;
        int min_dis;
        int min_time;
    };

    string Get_Minimum_Distance(string source, string destination)
    {
        int min = INT_MAX;
        string ans = "";
        unordered_map<string, bool> processed;
        deque<Pair> stack;

        Pair sp;
        sp.vname = source;
        sp.PathSoFar = source + "  ";
        sp.min_dis = 0;
        sp.min_time = 0;

        stack.push_front(sp);

        while (!stack.empty())
        {
            Pair rp = stack.front();
            stack.pop_front();

            if (processed.count(rp.vname))
            {
                continue;
            }

            processed[rp.vname] = true;

            if (rp.vname == destination)
            {
                int temp = rp.min_dis;
                if (temp < min)
                {
                    ans = rp.PathSoFar;
                    min = temp;
                }
                continue;
            }

            Vertex rpvtx = vertices[rp.vname];
            for (auto it = rpvtx.neighbours.begin(); it != rpvtx.neighbours.end(); it++)
            {
                string nbr = it->first;
                if (!processed.count(nbr))
                {
                    Pair np;
                    np.vname = nbr;
                    np.PathSoFar = rp.PathSoFar + nbr + "  ";
                    np.min_dis = rp.min_dis + rpvtx.neighbours[nbr];
                    stack.push_front(np);
                }
            }
        }
        ans = ans + to_string(min);
        return ans;
    }

    string Get_Minimum_Time(string source, string destination)
    {
        int min = INT_MAX;
        string ans = "";
        unordered_map<string, bool> processed;
        deque<Pair> stack;

        Pair sp;
        sp.vname = source;
        sp.PathSoFar = source + "  ";
        sp.min_dis = 0;
        sp.min_time = 0;

        stack.push_front(sp);

        while (!stack.empty())
        {
            Pair rp = stack.front();
            stack.pop_front();

            if (processed.count(rp.vname))
            {
                continue;
            }

            processed[rp.vname] = true;

            if (rp.vname == destination)
            {
                int temp = rp.min_time;
                if (temp < min)
                {
                    ans = rp.PathSoFar;
                    min = temp;
                }
                continue;
            }

            Vertex rpvtx = vertices[rp.vname];
            for (auto it = rpvtx.neighbours.begin(); it != rpvtx.neighbours.end(); it++)
            {
                string nbr = it->first;
                if (!processed.count(nbr))
                {
                    Pair np;
                    np.vname = nbr;
                    np.PathSoFar = rp.PathSoFar + nbr + "  ";
                    np.min_time = rp.min_time + 120 + 40 * rpvtx.neighbours[nbr];
                    stack.push_front(np);
                }
            }
        }
        double minutes = ceil((double)min / 60);
        ans = ans + to_string(minutes);
        return ans;
    }

    vector<string> get_Interchanges(string str)
    {
        vector<string> arr;
        string res[100];
        int count = 0;
        char *temp = strtok((char *)str.c_str(), "  ");
        while (temp != NULL)
        {
            res[count] = temp;
            count++;
            temp = strtok(NULL, "  ");
        }
        arr.push_back(res[0]);
        for (int i = 1; i < count - 1; i++)
        {
            int index = res[i].find('~');
            string s = res[i].substr(index + 1);

            if (s.length() == 2)
            {
                string prev = res[i - 1].substr(res[i - 1].find('~') + 1);
                string next = res[i + 1].substr(res[i + 1].find('~') + 1);

                if (prev == next)
                {
                    arr.push_back(res[i]);
                }
                else
                {
                    arr.push_back(res[i] + " ==> " + res[i + 1]);
                    i++;
                    count++;
                }
            }
            else
            {
                arr.push_back(res[i]);
            }
        }
        arr.push_back(to_string(count - 2));
        arr.push_back(res[count - 1]);
        return arr;
    }

    static void Create_Metro_Map(Metro_Graph &g)
    {
        g.addStation("Noida Sector 62~B");
        g.addStation("Botanical Garden~B");
        g.addStation("Yamuna Bank~B");
        g.addStation("Rajiv Chowk~BY");
        g.addStation("Vaishali~B");
        g.addStation("Moti Nagar~B");
        g.addStation("Janak Puri West~BO");
        g.addStation("Dwarka Sector 21~B");
        g.addStation("Huda City Center~Y");
        g.addStation("Saket~Y");
        g.addStation("Vishwavidyalaya~Y");
        g.addStation("Chandni Chowk~Y");
        g.addStation("New Delhi~YO");
        g.addStation("AIIMS~Y");
        g.addStation("Shivaji Stadium~O");
        g.addStation("DDS Campus~O");
        g.addStation("IGI Airport~O");
        g.addStation("Rajouri Garden~BP");
        g.addStation("Netaji Subhash Place~PR");
        g.addStation("Punjabi Bagh West~P");

        g.addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
        g.addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
        g.addEdge("Yamuna Bank~B", "Vaishali~B", 8);
        g.addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
        g.addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
        g.addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
        g.addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
        g.addEdge("Huda City Center~Y", "Saket~Y", 15);
        g.addEdge("Saket~Y", "AIIMS~Y", 6);
        g.addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
        g.addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
        g.addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
        g.addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
        g.addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
        g.addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
        g.addEdge("DDS Campus~O", "IGI Airport~O", 8);
        g.addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
        g.addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);    
        g.addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
    }

    static string *printCodelist()
    {
        cout << "List of station along with their codes:" << endl;
        vector<string> keys;
        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            keys.push_back(it->first);
        }
        int i = 1, j = 0, m = 1;
        string temp = "";
        string *codes = new string[keys.size()];
        char c;
        for (string key : keys)
        {
            int j = 0;
            codes[i - 1] = "";
            while (j < key.length())
            {
                temp = "";
                c = key[j];
                while (c > 47 && c < 58)
                {
                    temp += c;
                    j++;
                    c = key[j];
                }
                if ((c < 48 || c > 57) && c < 123)
                    temp += c;
                j++;
                codes[i - 1] += temp;
            }
            if (codes[i - 1].length() < 2)
                codes[i - 1] += toupper(temp[1]);

            cout << i << ". " << key << "\t";
            if (key.length() < (22 - m))
                cout << "\t";
            if (key.length() < (14 - m))
                cout << "\t";
            if (key.length() < (6 - m))
                cout << "\t";
            cout << codes[i - 1] << endl;
            i++;
            if (i == pow(10, m))
                m++;
        }
        return codes;
    }
};

unordered_map<string, Metro_Graph::Vertex> Metro_Graph::vertices;

int main()
{
    Metro_Graph g;
    Metro_Graph::Create_Metro_Map(g);

    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****" << endl;
    while (true)
    {
        cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout << "1. LIST ALL THE STATIONS IN THE MAP" << endl;
        cout << "2. SHOW THE METRO MAP" << endl;
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "5. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "6. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "7. EXIT THE MENU" << endl;
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7) : ";
        int choice = -1;
        cin >> choice;
        cout << "\n***********************************************************\n";
        if (choice == 7)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            g.display_Stations();
            break;

        case 2:
            g.display_Map();
            break;

        case 3:
        {
            vector<string> keys;
            string *codes = Metro_Graph::printCodelist();
            cout << "\n1. TO ENTER SERIAL NO. OF STATIONS\n2. TO ENTER CODE OF STATIONS\n3. TO ENTER NAME OF STATIONS\n";
            cout << "ENTER YOUR CHOICE:";
            int ch;
            cin >> ch;
            int j;

            string st1 = "", st2 = "";
            cout << "ENTER THE SOURCE AND DESTINATION STATIONS" << endl;
            if (ch == 1)
            {
                int a, b;
                cin >> a >> b;
                st1 = keys[a - 1];
                st2 = keys[b - 1];
            }
            else if (ch == 2)
            {
                string a, b;
                cin >> a >> b;
                for (j = 0; j < keys.size(); j++)
                {
                    if (a == codes[j])
                        break;
                }
                st1 = keys[j];
                for (j = 0; j < keys.size(); j++)
                {
                    if (b == codes[j])
                        break;
                }
                st2 = keys[j];
            }
            else if (ch == 3)
            {
                cin >> st1 >> st2;
            }
            else
            {
                cout << "Invalid choice" << endl;
                return 0;
            }

            unordered_map<string, bool> processed;
            if (!g.CheckIfContainsVertex(st1) || !g.CheckIfContainsVertex(st2) || !g.checkPath(st1, st2, processed))
                cout << "THE INPUTS ARE INVALID" << endl;
            else
                cout << "SHORTEST DISTANCE FROM " << st1 << " TO " << st2 << " IS " << g.dijkstra(st1, st2, false) << "KM" << endl;
            break;
        }

        case 4:
        {
            string sat1, sat2;
            cout << "ENTER THE SOURCE STATION: ";
            cin >> sat1;
            cout << "ENTER THE DESTINATION STATION: ";
            cin >> sat2;

            unordered_map<string, bool> processed1;
            cout << "SHORTEST TIME FROM (" << sat1 << ") TO (" << sat2 << ") IS " << g.dijkstra(sat1, sat2, true) / 60 << " MINUTES" << endl;
            break;
        }

        case 5:
        {
            string s1, s2;
            cout << "ENTER THE SOURCE AND DESTINATION STATIONS" << endl;
            cin >> s1 >> s2;

            unordered_map<string, bool> processed2;
            if (!g.CheckIfContainsVertex(s1) || !g.CheckIfContainsVertex(s2) || !g.checkPath(s1, s2, processed2))
                cout << "THE INPUTS ARE INVALID" << endl;
            else
            {
                vector<string> str = g.get_Interchanges(g.Get_Minimum_Distance(s1, s2));
                int len = str.size();
                cout << "SOURCE STATION : " << s1 << endl;
                cout << "SOURCE STATION : " << s2 << endl;
                cout << "DISTANCE : " << str[len - 1] << endl;
                cout << "NUMBER OF INTERCHANGES : " << str[len - 2] << endl;
                cout << "~~~~~~~~~~~~~" << endl;
                cout << "START  ==>  " << str[0] << endl;
                for (int i = 1; i < len - 3; i++)
                {
                    cout << str[i] << endl;
                }
                cout << str[len - 3] << "   ==>    END";
                cout << "\n~~~~~~~~~~~~~" << endl;
            }
            break;
        }

        case 6:
        {
            string ss1, ss2;
            cout << "ENTER THE SOURCE STATION: ";
            cin >> ss1;
            cout << "ENTER THE DESTINATION STATION: ";
            cin >> ss2;

            unordered_map<string, bool> processed3;
            if (!g.CheckIfContainsVertex(ss1) || !g.CheckIfContainsVertex(ss2) || !g.checkPath(ss1, ss2, processed3))
                cout << "THE INPUTS ARE INVALID" << endl;
            else
            {
                vector<string> str = g.get_Interchanges(g.Get_Minimum_Time(ss1, ss2));
                int len = str.size();
                cout << "SOURCE STATION : " << ss1 << endl;
                cout << "DESTINATION STATION : " << ss2 << endl;
                cout << "TIME : " << str[len - 1] << " MINUTES" << endl;
                cout << "NUMBER OF INTERCHANGES : " << str[len - 2] << endl;
                cout << "~~~~~~~~~~~~~" << endl;
                cout << "START  ==>  " << str[0] << endl;
                for (int i = 1; i < len - 3; i++)
                {
                    cout << str[i] << endl;
                }
                cout << str[len - 3] << "   ==>    END";
                cout << "\n~~~~~~~~~~~~~" << endl;
            }
            break;
        }

        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

    return 0;
}


