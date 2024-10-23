module circuit_1(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w;
        
wire y;
        
wire n;
        
not #(2) g1 (n,a);    
and #(5) g0 (w,c,n);
        

        
or #(9) g2 (y,a,b);
        
and #(5) g0 (0,y,w);

endmodule;