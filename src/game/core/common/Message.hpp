#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
    public:
        Message(double, int, int, int, void*);
        Message(const Message&);

        //bool operator()(const Message&) {};        
        bool operator<(const Message&) const;
        
         double delay;
            int    sender_id;
            int    receiver_id;
            int    type_id;
            void*  extra;
        
                double dispatch_time;
                
    private:
        
};                       

#endif
