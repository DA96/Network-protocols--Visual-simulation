// VISUAL SIMULATION OF GO BACK N PROTOCOL

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
void display_sf(int col);
void display_sn(int col);
void display_rn(int col);
void display_currfr(int col);
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
        drawPacket(4);
     //   start_timer(5);
    }

}

int moveAck_receiverToSender(int seq_no)
{
    int xi, yi;

    // moving frame from right to left
    // xi to be moved from 450 to 200

    setcolor(WHITE);
    for(xi = 250; xi>=0; xi=xi-50)      // where 250 is difference
    {
        drawAck(xi,10,seq_no);
        delay(500);
        cleardevice();
        drawSender();
        drawReceiver();
        drawPacket(3);
      //  if(xi==0) break;
     //   start_timer(5);
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

int main()
{

    initwindow(800,700);

    settextstyle(0,0,70);
    outtextxy(200,20," GO BACK N PROTOCOL");

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

    int n = 4;

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
    int ran_ackSeq = (ran_frameSeq+1) % 3;

    /*

    sf : sender first outsanding frame
    sn : sender next frame
    rn : receiver next frame
    sw : sender window size (n-1)

    curr_frame : current frame which is sent

    */

    int sf = 0,sn = 0,rn = 0,sw = n-1;
    int fr_lost = 0;    //frame lost


     outtextxy(75,250,"TIMER STARTED");
     delay(500);
     sn = sf+1;
     int timer=0;

     int curr_fr =0;
     int sf_timechk = 0;

    display_sf(fr_col[sf]);
    display_sn(fr_col[sn]);
    display_rn(fr_col[rn]);
    display_currfr(fr_col[curr_fr]);

    while(sf != n)
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
                    outtextxy(570,177,"FRAME RECEIVED");

                    if(curr_fr != ran_ackSeq)
                    {
                        moveAck_receiverToSender((curr_fr+1)%n);     //ACK RECEIVED SUCCESSFULLY
                        sf=(sf+1)%n;
                    }

                    else
                    {
                        int xia =250;
                        while(1)
                        {
                            drawAck(xia,0,(curr_fr+1)%n);
                            delay(500);
                            xia-=50;

                            cleardevice();
                            drawSender();
                            drawReceiver();
                            drawPacket(n);

                            if(xia == 150)
                            {
                                outtextxy(350,177,"ACK LOST");
                                delay(500);
                                break;
                            }

                        }

                    }
                }

                else
                    outtextxy(570,177,"NO ACTION");
            }

       // else DO NOTHING

        delay(500);
        curr_fr = sn%n;
        sn = (sn+1)%n;
        fr_lost=0;


        //timeout condition
        timer++;

        if(timer==2)
        {
            if(sf_timechk == sf)  // to check if sf has moved within timer or not
            {                     // sf_timechk checks for then another frame

                //Resend frame
                sn=(sf+1)%n;        //go back
                curr_fr = sf%n;
                ran_frameSeq = n+1;

                setcolor(COLOR(255,10,0));
                outtextxy(110,250,"TIMEOUT");
                delay(1500);

                outtextxy(100,200,"RESTART TIMER");
                outtextxy(100,177,"RESENDING FRAME");
                delay(1500);
            }

            else
                sf_timechk++;

            timer = 0;
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
