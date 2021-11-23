%% Stage 1, second order
R1 = 398e3;  % Ohms
R2 = 398e3;  % Ohms
C1 = 0.01e-6;  % Farads
C2 = 0.04e-6;  % Farads

num_coeff_1 = 1 / (R1*R2*C1*C2);
den_coeff_2 = (C1*(R1 + R2)) / (R1*R2*C1*C2);
den_coeff_3 = 1 / (R1*R2*C1*C2);

tf_num = num_coeff_1;
tf_den = [1 den_coeff_2 den_coeff_3];
H_1 = tf(tf_num, tf_den);
disp(H_1)

%% Stage 2, first order
R = 796e3;  % Ohms
C = 0.01e-6;  % Farads
H_2 = tf(1, [R*C 1]);
disp(H_2)

%% Total response
H_tot = H_1 * H_2;
bode(H_tot)