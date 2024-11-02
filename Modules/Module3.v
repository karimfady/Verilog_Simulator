module circuit_3(a, b, c, o);
input a;
input b;
input c;
        
output o;
        
wire w;
        
wire y;
        
wire n;
        
wire z;

or #(9) g2 (y,a,b);  
not #(2) g1 (n,b);
     
and #(5) g0 (w,y,c);
and #(5) g6 (z,n,c);
or #(9) g2 (o,w,z);

endmodule; 
