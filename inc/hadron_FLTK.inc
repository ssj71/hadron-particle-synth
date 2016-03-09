		FLpanel         "Hadron Controllers",500,300,100,100

iCTRjx1		= 20

iCTRvx1		= iCTRjx1 + 250
iCTRvx2		= iCTRvx1 + 55
iCTRvx3		= iCTRvx2 + 55
iCTRvx4		= iCTRvx3 + 55
iCTRvx5		= iCTRvx4 + 55

iCTRfx1		= iCTRvx1 + 10
iCTRfx2		= iCTRfx1 + 55
iCTRfx3		= iCTRfx2 + 55
iCTRfx4		= iCTRfx3 + 55

iCTRfx5		= iCTRfx4 + 80
iCTRfx6		= iCTRfx5 + 50

iCTRfx7		= iCTRfx6 + 70
iCTRfx8		= iCTRfx7 + 30
iCTRfx9		= iCTRfx8 + 30
iCTRfx10	= iCTRfx9 + 30

iCTRfy1		= 20
iCTRvy1		= iCTRfy1 + 240

gkJoyX, gkJoyY, gihJoyX, gihJoyY \
		FLjoy "XY", 0, 1, 0, 1, 0, 0, -1, -1, 220, 220, iCTRjx1, iCTRfy1
		FLsetVal_i	0.5, gihJoyX
		FLsetVal_i	0.5, gihJoyY	

ihs1 			FLbox "1", 1, 1, 12, 20, 20, iCTRjx1-20, iCTRfy1+200
ihs2 			FLbox "2", 1, 1, 12, 20, 20, iCTRjx1+220, iCTRfy1+200
ihs3 			FLbox "3", 1, 1, 12, 20, 20, iCTRjx1-20, iCTRfy1
ihs4 			FLbox "4", 1, 1, 12, 20, 20, iCTRjx1+220, iCTRfy1

iCTRhv1			FLvalue		" ", 		40,  20, iCTRvx1, iCTRvy1
gkCTRf1,iCTRhf1		FLslider	"sli_1", 0, 1, 0, 6, iCTRhv1, 	20, 220, iCTRfx1, iCTRfy1
iCTRhv2			FLvalue		" ", 		40,  20, iCTRvx2, iCTRvy1
gkCTRf2,iCTRhf2		FLslider	"sli_2", 0, 1, 0, 6, iCTRhv2, 	20, 220, iCTRfx2, iCTRfy1
iCTRhv3			FLvalue		" ", 		40,  20, iCTRvx3, iCTRvy1
gkCTRf3,iCTRhf3		FLslider	"sli_3", 0, 1, 0, 6, iCTRhv3, 	20, 220, iCTRfx3, iCTRfy1
iCTRhv4			FLvalue		" ", 		40,  20, iCTRvx4, iCTRvy1
gkCTRf4,iCTRhf4		FLslider	"sli_4", 0, 1, 0, 6, iCTRhv4, 	20, 220, iCTRfx4, iCTRfy1

        	FLpanel_end     
   		FLrun		
