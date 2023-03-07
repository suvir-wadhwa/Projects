from DoublyLinkedList import *
# from LinkedBinaryTree import *

def merge_linked_lists(srt_lnk_lst1, srt_lnk_lst2):

    def merge_sublists(first_node, second_node, output_list):
        if first_node.data is None and second_node.data is None:
            return None
        if (second_node.data is None) or (first_node.data and first_node.data < second_node.data):
            output_list.add_last(first_node.data)
            merge_sublists(first_node.next, second_node, output_list)
            return None
        elif (first_node.data is None) or (first_node.data and first_node.data > second_node.data):
            output_list.add_last(second_node.data)
            merge_sublists(first_node, second_node.next, output_list)
            return None
        else:
            output_list.add_last(first_node.data)
            output_list.add_last(second_node.data)
            merge_sublists(first_node.next, second_node.next, output_list)
            return None

    output_list = DoublyLinkedList()
    first_node = srt_lnk_lst1.header.next
    second_node = srt_lnk_lst2.header.next
    merge_sublists(first_node, second_node, output_list)

    return output_list

