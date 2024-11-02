module circuit_1(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w; 
wire y;
wire n;
        
not #(2) g0 (n,a);    
and #(5) g1 (w,c,n);
or #(9) g2 (y,a,b);
and #(5) g3 (o,y,w);
endmodule;
