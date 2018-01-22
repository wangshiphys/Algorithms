"""
Implementation of the disjoint set ADT with union-by-rank and path compression
"""


__all__ = [
    "DisjointSet",
]


class DisjointSet:
    """
    Implementation of the disjoint set ADT(Abstract Data Type)
    """

    def __init__(self, members):
        """Customize the newly created DisjointSet instance

        Parameters
        ----------
        members : iterable
            The members of the disjoint set. It should be a collection of
            hashable object.
        """

        self._index_table = {
            member: index for index, member in enumerate(members, 1)
        }
        self._ranks_or_parents = [0] * (len(members) + 1)
        # The first entry of this list will never be used
        self._ranks_or_parents[0] = None

    def _find(self, index):
        temp = self._ranks_or_parents[index]
        if temp <= 0:
            return index
        else:
            tree = self._find(temp)
            # The effect of the following assignment statement is that every
            # node on the path from `index` to the root has its parent
            # changed to the root, which implement the `path compression`
            # self._ranks_or_roots[index] = tree
            return tree

    def find(self, member):
        """Return the root of the class which `member` belong
        """

        return self._find(self._index_table[member])

    def isequivalent(self, member0, member1):
        """Return whether `member0` and `member1` belong to the same class
        """

        return self.find(member0) == self.find(member1)

    def _union_root(self, tree0, tree1):
        # This internal method perform the union-by-rank algorithm of two trees
        rank0 = self._ranks_or_parents[tree0]
        rank1 = self._ranks_or_parents[tree1]
        if rank1 < rank0:
            self._ranks_or_parents[tree0] = tree1
        else:
            if rank0 == rank1:
                self._ranks_or_parents[tree0] -= 1
            self._ranks_or_parents[tree1] = tree0

    def union(self, member0, member1):
        """
        Perform the union of two sets which contain `member0` and `member1`
        respectively. If `member0` and `member1` belong to the same set,
        the method do nothing.
        """

        tree0 = self.find(member0)
        tree1 = self.find(member1)
        if tree0 != tree1:
            self._union_root(tree0, tree1)

    def show(self):
        """Show all the none empty sets
        """

        forest = {
            tree: []
            for tree, rank in enumerate(self._ranks_or_parents[1:], 1)
            if rank <= 0
        }
        for member in self._index_table:
            tree = self.find(member)
            forest[tree].append(member)
        for tree, members in forest.items():
            msg0 = "The content of {}th set is:\n".format(tree)
            msg1 = str(members) + '\n'
            separator = '=' * max(len(msg0), len(msg1)) + '\n'
            print(msg0, msg1, separator, sep='')
        print("The number of sets: {}".format(len(forest)))


if __name__ == "__main__":
    members = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    disjset = DisjointSet(members)
    disjset.union('a', 'b')
    disjset.union('c', 'd')
    disjset.union('d', 'f')
    disjset.union('a', 'd')
    print(disjset.find('f'))
    disjset.show()
