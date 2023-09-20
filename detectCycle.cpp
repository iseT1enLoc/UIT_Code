#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
    ListNode *detectCycle(ListNode *head) {
        if(!head) return NULL;

        //initialize the two pointers
        ListNode*fast=head;
        ListNode*slow=head;

        bool cycleFound=false;

        while(fast&&fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;

            //found the cycle
            if(fast==slow)
            {
                cycleFound=true;
                break;
            }
        }

        if(!cycleFound) return NULL;

        //move the two pointer simutaneously
        //we have these pointer equally we will get 
        //the starting pointer
        while(head!=fast)
        {
            head=head->next;
            fast=fast->next;
        }
        return head;
    }
int main()
{

}