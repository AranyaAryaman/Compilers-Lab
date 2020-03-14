import matplotlib.pyplot as plt
import networkx as nx
def print_parse_tree(lst, labeldict, root=None):
    G = nx.DiGraph()
    G.add_nodes_from(labeldict)
    G.add_edges_from(lst)
    from networkx.drawing.nx_agraph import graphviz_layout
    pos=graphviz_layout(G, prog='dot')
    nx.draw_networkx_edges(G, pos, min_source_margin=10, min_target_margin=10)
    nx.draw_networkx_labels(G, pos, labels=labeldict)
    # plt.savefig('graph.png', pad_inches=12)
    plt.show()


currentnode = 0
nodelabels = dict()
nodelabels[0] = "start"
edgelist = list()
parentnode = dict()
with open("debug.txt", "r") as f:
    a = f.readlines()
a = list(map(lambda x: x.strip(), a))
assert (a[0] == "ENTER start")
assert (a[-1] == "EXIT start")
for i in a[1:-1]:
    if i.startswith("ENTER"):
        nodeid = len(edgelist)+1
        nodename = i[6:]
        # print(nodename)
        nodelabels[nodeid] = nodename
        if currentnode != None:
            edgelist.append((currentnode, nodeid))
            parentnode[nodeid] = currentnode
        currentnode = nodeid
    elif i.startswith("EXIT"):
        currentnode = parentnode[currentnode]
    elif i.startswith("MATCHED"):
        nodeid = len(edgelist)+1
        nodename = i[8:]
        nodelabels[nodeid] = nodename
        edgelist.append((currentnode, nodeid))
# print(edgelist)
print_parse_tree(edgelist, nodelabels)


# print_parse_tree(node list here, labels here)
