from LinkedBinaryTree import *
from math import *


def min_max(bin_tree):
        if bin_tree.size == 0:
                raise Exception('Tree is Empty')

        def subtree_min_max(subtree_root):
                if subtree_root is None:
                        return inf, -inf

                minVal = subtree_root.data
                maxVal = subtree_root.data

                min1, max1 = subtree_min_max(subtree_root.left)
                min2, max2 = subtree_min_max(subtree_root.right)

                min_val = min(minVal, min2, min1)
                max_val = max(maxVal, max1, max2)

                return (min_val, max_val)


        return subtree_min_max(bin_tree.root)




