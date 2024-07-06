#pragma once
#include"order.h"
#include<iostream>

struct Order_lk {
    Order order;
    Order_lk* next;
    Order_lk() { next = NULL; }
    Order_lk(Order o) { order = o; next = NULL; }
    Order_lk(const Order_lk& o) {
        order = o.order; next = o.next;
    }
};