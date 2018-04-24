// VISUAL SIMULATION OF STOP AND WAIT PROTOCOL

// Author : DIVYA AGARWAL

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;


void drawSender();
void drawReceiver();
void drawFrame(int xi,int yi,int seq_no);
void drawAck(int xi,int yi,int seq_no);
int start_timer(int time_secs, int frlost, int acklost, int seq_no, int fr_ackLost);


void drawSender()
{
    //SENDER
    rectangle(50,50,150,150);
    outtextxy(70,80,"SENDER");
    line(100,150,100,getmaxy());
}


void drawReceiver()
{
    //RECEIVER
    rectangle(400,50,500,150);
    outtextxy(420,80,"RECEIVER");
    line(450,150,450,getmaxy());
}


void drawFrame(int xi,int yi,int seq_no)
{
    /*
        Input parameters :
                            xi : x coordinate iterator
                            yi : y coordinate iterator
                        seq_no : frame sequence no.
    */

    rectangle(100+xi,170+yi,200+xi,200+yi);
    char str[1];
    sprintf(str, "FRAME %d", seq_no);
    outtextxy(120+xi,177+yi,str);
}


void drawAck(int xi,int yi,int seq_no)
{
    /*
        Input parameters :
                            xi : x coordinate iterator
                            yi : y coordinate iterator
                        seq_no : frame sequence no.
    */

    rectangle(100+xi,170+yi,200+xi,200+yi);
    char str[1];
    sprintf(str, "ACK %d", seq_no);
    outtextxy(120+xi,177+yi,str);
}



int start_timer(int time_secs, int frlost, int acklost, int seq_no, int fr_ackLost)
{
    /*
        Input Parameters :
                            time_secs : time in seconds for which timer is set
                            frlost    : frame lost
                            acklost   : ack lost
                            seq_no    : sequence no. of frame
        Return Value :
                        ack_arr : flag for ack arrived
    */

    setcolor(15);
    circle(50,300,25);
    outtextxy(25,330,"TIMER");
    int t = time_secs, temp;
    int xif =0, fr = 0, xia = 250, ack_arr =0;

    /*
            xif     : x coordinate iterator for frame
            fr      : flag for frame received
            xia     : x coordinate iterator for ack
            ack_arr : flag for ack arrived
    */

    outtextxy(10,180,"SENDING");
    outtextxy(12,200,"FRAME");

    while(1)
    {

        if(frlost == 0 && acklost == 0)
        {
                   //FRAME SENT SUCCESSFULLY
            if(xif != 250)
            {
                drawFrame(xif,0,seq_no);
                xif+=50;
            }
            else
            {
                if(fr_ackLost)
                {
                    outtextxy(470,177,"DUPLICATE FRAME");
                    outtextxy(470,195," DISCARDED");
                    delay(500);
                    fr_ackLost = 0;
                    fr = 1;
                }

                else if(!fr)
                {
                    outtextxy(470,177,"FRAME RECEIVED");
                    fr = 1;
                }
            }


                //ACK ARRIVED SUCCESSFULLY
            if(fr)
            {
                if(xia!=0)
                {
                    drawAck(xia,10,!(seq_no));
                    xia-=50;
                }

                else
                {
                    outtextxy(10,177,"ACK ARRIVED");
                    ack_arr = 1;
                    delay(200);
                }
            }

        }


        else if(frlost == 0 && acklost == 1)
        {
                   //FRAME SENT SUCCESSFULLY
            if(xif != 250)
            {
                drawFrame(xif,0,seq_no);
                xif+=50;
            }
            else
            {
               if(!fr)
                {
                    outtextxy(470,177,"FRAME RECEIVED");
                    fr = 1;
                }
            }


                //ACK LOST
            if(fr)
            {
                if(xia!=150)
                {
                    drawAck(xia,10,!(seq_no));
                    xia-=50;
                }

                else
                  if(!ack_arr)
                {
                    outtextxy(250,177,"ACK LOST");
                    ack_arr = 0;
                }
            }

        }


        else    //FRAME LOST
        {
            if(xif != 150)
            {
                drawFrame(xif,0,seq_no);
                xif+=50;
            }
            else
            {
               if(!fr)
                {
                    outtextxy(250,177,"FRAME LOST");
                    fr = 1;
                }
            }

        }


        temp = t;
        char str[3];
        sprintf(str, "%d", t);
        setcolor(COLOR(255,10,10));
        outtextxy(45,290,str);
        delay(1000);
        t = temp;
        t--;
        if(t < 0) break;
        cleardevice();
        setcolor(WHITE);
        drawSender();
        drawReceiver();
        circle(50,300,25);
        outtextxy(25,330,"TIMER");
    }

    return ack_arr;

}



int main()
{
    //getmaxx() = 639   getmaxy() = 479

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    outtextxy(200,10,"STOP AND WAIT PROTOCOL");
    drawSender();
    drawReceiver();
    delay(1000);

    int n = 4;
    int packet[n];
    int seqNo = 0;
    int fr_ackLost = 0;     //frame received and ack lost

    //initializing seqNo of frames in packet
    for(int i=0; i<n; i++)
    {
        packet[i] = seqNo;
        seqNo = !(seqNo);
    }


    srand((int) time(0));
    int ran_frameSeq = rand() % 3;
    int ran_ackSeq = (ran_frameSeq+1) % 3;
    int timeout; //= !(start_timer(12)); //if ack_arr = 1, then timeout=0, else timeout=1


    for(int i=0; i<n; i++)
    {
        if(i == ran_frameSeq)
        {
            timeout = !(start_timer(12,1,0,packet[i],0));
        }
        else
        {
            if(i == ran_ackSeq)
               {
                    timeout = !(start_timer(12,0,1,packet[i],0));
                    fr_ackLost = 1;
               }
            else
                timeout = !(start_timer(12,0,0,packet[i],0));
        }

        if(timeout)
        {
            // if ack doesn't reach at sender in set time, then resend that frame

            outtextxy(10,250,"TIMEOUT");
            delay(1500);
            setcolor(YELLOW);
            outtextxy(10,250,"RESTART TIMER");
            outtextxy(10,177,"RESENDING FRAME");
            delay(1500);
            int temp = start_timer(12,0,0,packet[i],fr_ackLost);
        }

        fr_ackLost = 0;

    }


    getch();
    closegraph();
    return 0;
}
