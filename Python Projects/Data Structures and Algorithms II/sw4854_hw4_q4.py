from math import *
from LinkedBinaryTree import *


def min_and_max(bin_tree):
    def subtree_min_and_max(root):
        max_val = root.data
        min_val = root.data
        if root.left != None:
            min_result, max_result = subtree_min_and_max(root.left)
            min_val = min(min_val, min_result)
            max_val = max(max_val, max_result)
        if root.right != None:
            min_result, max_result = subtree_min_and_max(root.right)
            min_val = min(min_val, min_result)
            max_val = max(max_val, max_result)

        return (min_val, max_val)

    if bin_tree.is_empty():
        raise Exception("Binary Tree is empty")
    else:
        return subtree_min_and_max(bin_tree.root)
