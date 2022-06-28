#include <iostream>
#include <cstring>

using namespace std;

const int maxN = 2e6;

struct Node {
    int vertex;
    Node *next;
};

Node *new_node(int vertex) {
    Node *node = new Node;
    node -> vertex = vertex;
    node -> next = NULL;
    return node;
}

struct Graph {
    int numberVertex;
    Node **edg;
    int *vis;
    FILE *fptr;
public:
    void add_edg(int u, int v) {
        // add u->v
        Node *tmp = new_node(v);
        tmp -> next = edg[u] -> next;
        edg[u] -> next = tmp;

        // add v->u
        tmp = new_node(u);
        tmp -> next = edg[v] -> next;
        edg[v] -> next = tmp;
    }

    void bfs(int u) {
        fptr = fopen("BFS.txt", "w");
        fprintf(fptr, "BFS from %d\n", u);
        memset(vis, 0, sizeof(int)*numberVertex);

        vis[u] = 1;

        Node *head, *tail;
        head = new_node(u);
        tail = head;
        while(head != NULL) {
            int vertex = head -> vertex;
            fprintf(fptr, "%d\n", vertex);

            Node *next_node = edg[vertex] -> next;
            while(next_node != NULL) {
                if (!vis[next_node->vertex]) {
                    Node *tmp = new_node(next_node->vertex);
                    tail -> next = tmp;
                    tail = tail ->next;
                    vis[ next_node -> vertex ] = 1;
                }
                next_node = next_node -> next;
            }
            head = head -> next;
        }
        fclose(fptr);
    }

    void dfs(int u) {
        memset(vis, 0, sizeof(int)*numberVertex);
        vis[u] = 1;
        fptr = fopen("DFS.txt", "w");
        fprintf(fptr, "DFS from %d\n", u);

        Node *node_stack = new_node(u);
        while(node_stack != NULL) {
            int vertex = node_stack -> vertex;
            fprintf(fptr, "%d\n",vertex);

            Node *next_node = edg[vertex] -> next;

            node_stack = node_stack -> next;

            while(next_node != NULL) {
                if (!vis[next_node->vertex]) {
                    Node *tmp = new_node(next_node->vertex);

                    // stack rong
                    if (node_stack == NULL) {
                        node_stack = tmp;
                    } else {
                        tmp -> next = node_stack;
                        node_stack = tmp;
                    }

                    vis[ next_node -> vertex ] = 1;
                }
                next_node = next_node -> next;
            }

        }

        fclose(fptr);

    }

    void flag(int u) {
        vis[u] = 1;

        Node *node_stack = new_node(u);
        while(node_stack != NULL) {
            int vertex = node_stack -> vertex;

            Node *next_node = edg[vertex] -> next;

            node_stack = node_stack -> next;

            while(next_node != NULL) {
                if (!vis[next_node->vertex]) {
                    Node *tmp = new_node(next_node->vertex);

                    // stack rong
                    if (node_stack == NULL) {
                        node_stack = tmp;
                    } else {
                        tmp -> next = node_stack;
                        node_stack = tmp;
                    }

                    vis[ next_node -> vertex ] = 1;
                }
                next_node = next_node -> next;
            }

        }

    }

    void count_connected_component() {
        int res = 0;
        memset(vis, 0, sizeof(int)*numberVertex);
        for (int i = 0; i < numberVertex; i++) {
            if (!vis[i]) {
                res ++;
                vis[i] = 1;
                flag(i);
            }
        }
        printf("number connected component: %d \n", res);
    }

    void edg_adjacent(int u) {
        printf("adjacent with %d\n", u);
        Node *tmp = edg[u] -> next;
        while(tmp != NULL) {
            printf("%d\n", tmp -> vertex);
            tmp = tmp -> next;
        }
    }
};

Graph *new_graph (int numberVertex) {
    Graph *graph = new Graph;
    graph -> numberVertex = numberVertex;

    graph -> edg = new Node* [numberVertex];
    for (int i = 0; i < numberVertex; i++) {
        graph -> edg[i] = new_node(i);
    }

    graph -> vis = new int[numberVertex];

    return graph;
}

Graph *graph;
void read_data(string FILEINPUT) {
    graph = new_graph(maxN);

    char file_input[20] = {};
    for (int i = 0; i < FILEINPUT.size(); i++)
        file_input[i] = FILEINPUT[i];

    FILE *fptr = fopen(file_input, "r");
    int u, v;
    int n = 0, m = 0;
    while (fscanf(fptr, "%d %d", &u, &v) != EOF) {
        if (u > n)
            n = u;
        if (v > n)
            n = v;
        m++;
        graph -> add_edg(u, v);
    }

    fclose(fptr);
}

int main() {

    printf("------PROJECT I------\n");
    printf("SV: Truong Nho Nhat Quang\n");
    printf("MSSV: 20193237\n");
    printf("Choose File input:\n");

    printf("1. roadNet-CA\n");
    printf("2. roadNet-PA\n");
    printf("3. roadNet-TX\n");

    string tmp;
    string FILEINPUT = "";
    cin >> tmp;
    if (tmp == "1")
        FILEINPUT = "roadNet-CA.txt";
    else if (tmp == "2")
        FILEINPUT = "roadNet-PA.txt";
    else FILEINPUT = "roadNet-TX.txt";

    cout << "File input: " << FILEINPUT << "\n";

    read_data(FILEINPUT);

    while(true) {
        printf("Press 1 to BFS\n");
        printf("Press 2 to DFS\n");
        printf("Press 3 to count connected component\n");
        printf("Press other key to exit\n");

        string s;
        cin >> s;
        if (s == "1") {
            printf("BFS from :");
            int u;
            scanf("%d", &u);
            graph->bfs(u);
            printf("Done! Check in BFS.txt!\n");
        }

        else if (s == "2") {
            printf("DFS from :");
            int u;
            scanf("%d", &u);
            graph->dfs(u);
            printf("Done! Check in DFS.txt!\n");
        }


        else if (s == "3") {
            graph->count_connected_component();
        }

        else break;

    }

    return 0;
}
