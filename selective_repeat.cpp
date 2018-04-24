// VISUAL SIMULATION OF SELECTIVE REPEAT PROTOCOL

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
void drawNAck(int xi,int yi,int seq_no);
int moveFrame_senderToReceiver(int seq_no);
int moveAck_receiverToSender(int seq_no,int nack);
void display_sf(int col);
void display_sn(int col);
void display_rn(int col);
void display_currfr(int col);
void resend_frame(int seq_no,int rw_end);
void drawPacket(int n);


void drawSender()
{
    //SENDER
    rectangle(150,50,250,150);
    outtextxy(170,80,"SENDER");
    line(200,150,200,getmaxy());
}


void drawReceiver()
{
    //RECEIVER
    rectangle(500,50,600,150);
    outtextxy(520,80,"RECEIVER");
    line(550,150,550,getmaxy());
}


void drawFrame(int xi,int yi,int seq_no)
{
    /*
        Input parameters :
                            xi : x coordinate iterator
                            yi : y coordinate iterator
                        seq_no : frame sequence no.
    */

    rectangle(200+xi,170+yi,300+xi,200+yi);
    char str[1];
    sprintf(str, "FRAME %d", seq_no);
    outtextxy(220+xi,177+yi,str);
}


void drawAck(int xi,int yi,int seq_no)
{
    // DRAWS ACKNOWLEDGEMENT
    /*
        Input parameters :
                            xi : x coordinate iterator
                            yi : y coordinate iterator
                        seq_no : frame sequence no.
    */

    rectangle(200+xi,170+yi,300+xi,200+yi);
    char str[1];
    sprintf(str, "ACK %d", seq_no);
    outtextxy(220+xi,177+yi,str);
}


void drawNAck(int xi,int yi,int seq_no)
{
    // DRAWS NEGATIVE ACK
    /*
        Input parameters :
                            xi : x coordinate iterator
                            yi : y coordinate iterator
                        seq_no : frame sequence no.
    */

    rectangle(200+xi,170+yi,300+xi,200+yi);
    char str[1];
    sprintf(str, "NAK %d", seq_no);
    outtextxy(220+xi,177+yi,str);
}


int moveFrame_senderToReceiver(int seq_no)
{
    int xi, yi;

    // moving frame from left to right
    // xi to be moved from 200 to 450

   outtextxy(110,180,"SENDING");
    outtextxy(112,200,"FRAME");
    delay(1000);

    for(xi = 0; xi<=250; xi=xi+50)      // where 250 is difference
    {
        drawFrame(xi,0,seq_no);
        delay(500);
        cleardevice();
        drawSender();
        drawReceiver();
        drawPacket(8);
    }

}

int moveAck_receiverToSender(int seq_no,int nack)
{
    int xi, yi;

    // moving frame from right to left
    // xi to be moved from 450 to 200

    setcolor(WHITE);
    for(xi = 250; xi>=0; xi=xi-50)      // where 250 is difference
    {
        if(nack==0)
        drawAck(xi,10,seq_no);
        else
            drawNAck(xi,10,seq_no);
        delay(500);
        cleardevice();
        drawSender();
        drawReceiver();
        drawPacket(8);
    }

    outtextxy(115,180,"ACK");
    outtextxy(117,200,"ARRIVED");
    delay(1000);
}


void drawPacket(int n)
{
    // DRAWS COLOR PACKETS
    // INPUT PARAMETER : n: NUMBER OF PACKETS TO BE DRAWN

    int rad =0;
    int fr_col[4];
    fr_col = {COLOR(255,100,0),14,COLOR(0,100,255),COLOR(50,255,0)};

    for(int i=0;i<n;i++)
    {
            setcolor(15);
            circle(300+rad+rad,25,20);
            setfillstyle(1,fr_col[i]);
            floodfill(300+rad+rad,25,15);
            rad+=20;
    }
}


void display_sf(int col)
{
        setcolor(col);
        outtextxy(275,55,"Sf");
        delay(1500);
}

void display_sn(int col)
{
        setcolor(col);
        outtextxy(300,55,"Sn");
        delay(1500);
}

void display_rn(int col)
{
        setcolor(col);
        outtextxy(400,55,"Rn");
        delay(1500);
}

void display_currfr(int col)
{
        setcolor(col);
        outtextxy(275,75,"curr_frame");
        delay(1500);
}


void resend_frame(int seq_no,int rw_end)
{
    moveFrame_senderToReceiver(seq_no);
    moveAck_receiverToSender(rw_end,0);

}


int main()
{

    initwindow(800,700);

    settextstyle(0,0,70);
    outtextxy(200,20," SELECTIVE REPEAT PROTOCOL");

    int fr_col[4];
    fr_col = {COLOR(255,100,0),14,COLOR(0,100,255),COLOR(50,255,0)};


    outtextxy(250,100,"INTRODUCTION");
    delay(1000);

    cleardevice();

    for(int i=0; i<4;i++)
    {
        setcolor(fr_col[i]);

         if(i==0)
         {
            outtextxy(250,250,"0");
            setcolor(15);
            circle(400,250,100);
            setfillstyle(1,fr_col[i]);
            floodfill(400,250,15);
        }

         if(i==1)
          {
            outtextxy(250,250,"1");
            setcolor(15);
            circle(400,250,100);
            setfillstyle(1,fr_col[i]);
            floodfill(400,250,15);
          }

         if(i==2)
          {
            outtextxy(250,250,"2");
            setcolor(15);
            circle(400,250,100);
            setfillstyle(1,fr_col[i]);
            floodfill(400,250,15);
          }

         if(i==3)
          {
            outtextxy(250,250,"3");
            setcolor(15);
            circle(400,250,100);
            setfillstyle(1,fr_col[i]);
            floodfill(400,250,15);
          }

            delay(1500);
            cleardevice();
    }

    closegraph();

    initwindow(800,700);

    int n = 8;      // no. of packets

    drawSender();
    drawReceiver();
    drawPacket(n);
    delay(1000);


    int packet[n];

    //initializing seqNo of frames in packet
    for(int i=0; i<n; i++)
    {
        packet[i] = i;
    }



    srand((int) time(0));
    int ran_frameSeq = rand() % 3;
  //  int ran_ackSeq = (ran_frameSeq+1) % 3;



    /*

    sf : sender first outsanding frame
    sn : sender next frame
    rn : receiver next frame
    sw : sender window size (atmost n/2)
    rw : receiver window size (atmost n/2)

    curr_frame : current frame which is sent
    sw_end : end of sender window
    rw_end : end of receiver window

    */

    int sf = 0,sn = 0,rn = 0,sw = n/2,rw = n/2;
    int fr_lost = 0;    //frame lost

     outtextxy(75,250,"TIMER STARTED");
     delay(500);
     sn = sf+1;

     int curr_fr =0;
     int sw_end = sw+sf-1;
     int sw_end_initial = sw_end;
     int rw_end = rw+rn-1;


    display_sf(fr_col[sf]);
    display_sn(fr_col[sn]);
    display_rn(fr_col[rn]);
    display_currfr(fr_col[curr_fr]);

    while(1)
    {

        if(curr_fr != ran_frameSeq)
            {
                moveFrame_senderToReceiver(curr_fr);
            }

        else
          {
              fr_lost=1;

            int xif =0;
            while(1)
            {
                drawFrame(xif,0,curr_fr);
                delay(500);
                xif+=50;

                cleardevice();
                drawSender();
                drawReceiver();
                drawPacket(n);

                if(xif == 150)
                {
                    outtextxy(350,177,"FRAME LOST");
                    delay(500);
                    break;
                }

            }
          }


            if(!fr_lost)
            {
                if(rn == curr_fr)
                {
                    rn = (rn+1)%n;
                    rw_end = (rw_end+1)%n;
                    outtextxy(570,177,"FRAME RECEIVED");

                    moveAck_receiverToSender((curr_fr+1)%n,0);     //ACK RECEIVED SUCCESSFULLY
                    sf=(sf+1)%n;
                    sw_end = (sw_end+1)%n;   //sliding window
                }

                else
                    outtextxy(570,177,"FRAME RECEIVED");
            }


        delay(500);
        fr_lost=0;


        //timeout condition
        if(sn==sw_end_initial+1 && sf <= sw_end_initial)

        {
            ran_frameSeq = n+1;
            moveAck_receiverToSender(rn,1);
            setcolor(COLOR(255,10,0));
            outtextxy(110,250,"TIMEOUT");
            delay(1500);

            outtextxy(100,200,"RESTART TIMER");
            outtextxy(100,177,"RESENDING FRAME");
            delay(1500);
            resend_frame(sf,rw_end);

            sf = (rw_end)%n;
            sw_end = (sf+sw-1)%n;
            curr_fr = sf%n;
            sn = (sf+1)%n;
            sw_end_initial = sw_end;
            rn = (rw_end)%n;
            rw_end = (rn+rw-1)%n;

        }

        else
        {
            curr_fr = sn%n;
            sn = (sn+1)%n;
        }

    display_sf(fr_col[sf]);
    display_sn(fr_col[sn]);
    display_rn(fr_col[rn]);
    display_currfr(fr_col[curr_fr]);
}

    getch();
    closegraph();
    return 0;
}

