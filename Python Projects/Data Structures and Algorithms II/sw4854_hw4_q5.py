from LinkedBinaryTree import *


def is_height_balanced(bin_tree):
    if bin_tree is None:
        return
    def subtree_height(root):
        if root == None:
            return 0
        check_left = subtree_height(root.left)
        check_right = subtree_height(root.right)
        if (check_left < 0) or (check_right < 0) or (check_left - check_right) > 1:
            return -1
        return max(check_left, check_right) + 1

    return subtree_height(bin_tree.root) >= 0



