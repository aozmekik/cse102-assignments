# CSE 102 – Computer

# Programming

# HW 11

## Last Submission Date: May 27, 2018 –23:

```
Purpose of this assignment is developing a booking program for hotels. The basic concept of this
program consist of two lists; Rooms and customers. The hotel is the list of the rooms basically. Any
room in the hotel has number, capacity, floor and customer properties. The customers has
surname, name, age and gender properties. In this assignment you will develop the system with
linked list data structure. You need to construct a list like shown in below:
```
```
As shown above, there could be zero, one or more customers in a room. You need to link
them together also. All rooms and customers are given with text files which are available
on moodle under assignment 11 topics. First read rooms from the rooms.txt file and
construct the room list. After that, read customers from customers.txt file and link
customers each other’s that are in same room and after that link the partial list with the
room. You need to write the code of functions which are shown in below.
```
```
add_room_to_end(): The function add a room to the end of the room list.
```
```
add_room_after_room_number (): The function add a room to after the given room
number. If the given room does not exists, add it to the end of the list.
```
```
add_customer_to_end(): The function add a customer to the end of the partial customer
list.
```
```
link_customers_to_room(): The function adds partial customer list to a room.
```
```
remove _room (): The function removes the room indicated by the room number.
```
```
show_vacancy(): The function list all available rooms that don’t have any customer.
```
```
Room 1 Room 2 Room 3 ....
```
```
Customer 1
```
```
Customer 2
```
```
Customer 7
```

**get_by_floor():** The function lists the rooms with the given floor number.

**print_list ():** The function prints the room list with customers as shown below:

**Room 101 (Floor 1 – capacity 3 x):**

**-** > Cedric Stone ( 28 – Male)
**-** > Elisabeth Kubiak (28 – Female)
**Room 102 (Floor 1 – capacity 2 x):**
- > Empty
**Room 3 03 (Floor 3 – capacity 1 x):**
- > Dora Waage
...

**Note that** the given functions that are on above are just represents of the functions not
the prototypes.

**General:**

**1.** Obey honor code principles.
**2. Read your homework carefully** and follow the directives about the I/O format (data file names,
file formats, etc.) and submission format **strictly**. Violating any of these directives will be penalized.
**3.** Obey coding convention.
**4**. Your submission is studentnumber.zip and include the following files and NOTHING MORE (no
data files, object files, etc):
     HW11.c
**5.** Do not use non-English characters in any part of your homework (in body, file name, etc.).
**6.** Deliver the print out of your work until the last submission date.
**7.** For questions about homework, you can send an email to b.koca@gtu.com.tr


