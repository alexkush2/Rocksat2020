%Clearing all previous definitions and closing open programs.
clear all
close all
clc

%Calculating nose half-angle from geometry of rocket.
Dnose=0.3556;             %Diameter of nose,m
Lnose=1.0518;             %Length of nose,m
thetac=atand(Dnose/Lnose); %Half-angle of nose, degrees

%Defines specific heats and specific heat ratio.
cp=1004;     %J/(kg*K)
cv=717.1;    %J/(kg*K)
gamma=1.40;  %(cp/cv),dimensionless 

%Defines gravity.
g=9.806; %m/(s^2)

%Defines specific gas constant of air.
R=287.0; %J/(kg*K)

%Defines temperature gradients for each altitude range. Term after
%underscore denotes valid altitude range.
Tz_1=-6.5*10^(-3); %For 0km to 11km, K/m
Tz_2=0;            %For 11km to 20km, K/m
Tz_3=1*10^(-3);    %For 20km to 32km, K/m
Tz_4=2.8*10^(-3);  %For 32km to 47km, K/m

%Defines reference properties of air. Term after underscore denotes 
%altitude in kilometers.
p_sea=101300;     %Atmospheric pressures, Pa
p_11=22631.7;
p_20=5474.7;
p_32=867.98;

rho_sea=1.225;     %Densities of air, kg/(m^3)
rho_11=0.3639;
rho_20=0.08803;
rho_32=0.01322;

T_sea=288.2;       %Static temperatures of air, K
T_11=216.7;
T_20=216.7;
T_32=228.7;

%Importing RockSat 2011 Radar Data for the Ascent.
%% Initialize variables.
filename = 'C:\Users\Aprt 2F\Documents\MATLAB\RadarData_Ascent.txt';
delimiter = '\t';
%% Format string for each line of text:
%   column1: double (%f)
%	column2: double (%f)
%   column3: double (%f)
formatSpec = '%f%f%f%[^\n\r]';
%% Open the text file.
fileID=fopen(filename,'r');
%% Read columns of data according to format string.
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter,  'ReturnOnError', false);
%% Close the text file.
fclose(fileID);
%% Allocate imported array to column variables.
t=dataArray{:, 1}; %Time, s.  Begins at 9.9s
Z=dataArray{:, 2}; %Altitude, m.  Begins at 5041m
V1=dataArray{:, 3}; %Velocity, m/s.  Begins at 588 m/s

%Calculate upstream static properties of air at given altitude using
%appropriate equations. Adjacent "1" next to variables denotes properties 
%upstream of the tip of the nose cone.

%Creating row vectors to store upstream static and stagnation air
%properties.
p1set=zeros(1,length(Z));
rho1set=zeros(1,length(Z));
T1set=zeros(1,length(Z));
a1set=zeros(1,length(Z));
M1set=zeros(1,length(Z));
po1set=zeros(1,length(Z));
rhoo1set=zeros(1,length(Z));
To1set=zeros(1,length(Z));

%Creating row vectors to store post-shock static and stagnation air
%properties.
thetasset=zeros(1,length(Z));
M2set=zeros(1,length(Z));
p2set=zeros(1,length(Z));
rho2set=zeros(1,length(Z));
T2set=zeros(1,length(Z));
po2set=zeros(1,length(Z));
To2set=zeros(1,length(Z));

for jj=1:1:length(Z);
        if (0<=Z(jj)) && (Z(jj)<11000); 
            p1=p_sea.*((1+(Tz_1/T_sea).*Z(jj)).^(-g/(R*Tz_1)));
            rho1=rho_sea.*((1+(Tz_1/T_sea).*Z(jj)).^(-g/(R*Tz_1)-1));
            T1=T_sea.*(1+(Tz_1/T_sea).*Z(jj));
            p1set(1,jj)=p1;
            rho1set(1,jj)=rho1;
            T1set(1,jj)=T1;
        elseif (11000<=Z(jj)) && (Z(jj)<20000);
            p1=p_11.*exp((-g/(R*T_11)).*(Z(jj)-11000));
            rho1=rho_11.*exp((-g/(R*T_11)).*(Z(jj)-11000));
            T1=216.7;
            p1set(1,jj)=p1;
            rho1set(1,jj)=rho1;
            T1set(1,jj)=T1;
        elseif (20000<=Z(jj)) && (Z(jj)<32000); 
            p1=p_20.*((1+(Tz_3/T_20).*(Z(jj)-20000)).^(-g/(R*Tz_3)));
            rho1=rho_20.*((1+(Tz_3/T_20).*(Z(jj)-20000)).^(-g/(R*Tz_3)-1));
            T1=T_20.*(1+(Tz_3/T_20).*(Z(jj)-20000));
            p1set(1,jj)=p1;
            rho1set(1,jj)=rho1;
            T1set(1,jj)=T1; 
        elseif (32000<=Z(jj)) && (Z(jj)<47000); 
            p1=p_32.*((1+(Tz_4/T_32).*(Z(jj)-32000)).^(-g/(R*Tz_4)));
            rho1=rho_32.*((1+(Tz_4/T_32).*(Z(jj)-32000)).^(-g/(R*Tz_4)-1));
            T1=T_32.*(1+(Tz_4/T_32).*(Z(jj)-32000));
            p1set(1,jj)=p1;
            rho1set(1,jj)=rho1;
            T1set(1,jj)=T1; 
        elseif (47000<Z(jj)); 
            display('Property Approximations Not Valid In This Range') 
        end
        
         %Calculating upstream speed of sound and Mach number.   
         a1=(gamma*R*T1)^.5;              %Local speed of sound, m/s
         a1set(1,jj)=a1;
         M1=V1(jj)./a1set(1,jj);          %Local Mach number, dimensionless
         M1set(1,jj)=M1;

         %Calculating upstream stagnation properties of air.  "o" denotes 
         %stagnation property.
         po1=p1*(((1+(gamma-1)/2*M1^2))^(gamma/(gamma-1))); %Upstream stagnation pressure, Pa.  (Eq. 3.15, Gas Dynamics)
         po1set(1,jj)=po1;
         rhoo1=rho1*(((1+(gamma-1)/2*M1^2))^(1/(gamma-1))); %Upstream stagnation density, kg/(m^3).  (Eq. 3.17, Gas Dynamics)
         rhoo1set(1,jj)=rhoo1;
         To1=T1*(1+(gamma-1)/2*(M1^2));                     %Upstream stagnation temperatuer, K.  (Eq. 3.12, Gas Dynamics)
         To1set(1,jj)=To1;     
end

%%
%Iterative method For determining the shock angle based on incoming Mach
%number.  
%========================================================================%
%========================================================================%
thetacrad=thetac*(pi/180);  %Theta Cone in radians
beta=80:-.01:0; %Shock Angle in Degrees
betarad=beta*pi/180; %Shock Angle in Radians
Shockangle=zeros(3,length(M1set)); %Empty Compile Matrix

%Shock Equation from,
%http://www.cs.sandia.gov/~dwbarne/Project_shocks/shocks.pdf
%Equation can be found at the top of page 5
ShockEq=@(M,beta) (1-(13*gamma^2-2*gamma-11)/(24*(gamma+1)^2))*beta^4 ...
-thetacrad*beta^3-(14*gamma+10)/(12*(gamma+1)^2*M^2)*beta^2-1/(6*(gamma+1)^2*M^4);
     
 %Iterative For Loop
 for kk=1:length(M1set);
    for ii=1:length(beta)
        f=abs(ShockEq(M1set(kk),betarad(ii)));
        if round(f*100)/100 < .01 
        Shockangle(2,kk)=beta(ii);
        Shockangle(1,kk)=M1set(kk);
        Shockangle(3,kk)=betarad(ii);
        break
        end
     end
 end      
thetasset=Shockangle(2,:);
%Shock Angle Matrix is arranged as follows. 
%Col.#1 - Upstream Mach Number   Col.#2 - Shock Angle [deg]  Col.#3 Shock Angle [rad] 

%%
%With shock angle, Eq 6.17 for oblique shocks can be used to find
%M2, static, and stagnation properties after shock (Eq 6.10-6.14)
        
 for jj=1:1:length(Z);       
        M2set(jj)=sqrt((1+(gamma-1)/2*(M1set(jj).^2))/((gamma*(M1set(jj).^2)*(sind(thetasset(jj))^2))-(gamma-1)/2)+(M1set(jj).^2)*(cosd(thetasset(jj))^2)/((1+(gamma-1)/2*(M1set(jj).^2)*(sind(thetasset(jj))^2))));
        p2set(jj)=p1set(jj)*((2*gamma*(M1set(jj)^2)*(sind(thetasset(jj))^2)/(gamma+1)-(gamma-1)/(gamma+1)));
        rho2set(jj)=rho1set(jj)*(((gamma+1)*(M1set(jj)^2)*(sind(thetasset(jj))^2))/((gamma-1)*(M1set(jj)^2)*(sind(thetasset(jj))^2)+2));
        T2set(jj)=T1set(jj)*(1+(gamma-1)/2*(M1set(jj)^2)*(sind(thetasset(jj))^2))*(2*gamma/(gamma-1)*(M1set(jj)^2)*(sind(thetasset(jj))^2)-1)/(((gamma+1)^2)/(2*(gamma-1))*(M1set(jj)^2)*(sind(thetasset(jj))^2));
        po2set(jj)=po1set(jj)*((((gamma+1)/2*(M1set(jj)^2)*(sind(thetasset(jj))^2))/(1+(gamma-1)/2*(M1set(jj)^2)*(sind(thetasset(jj))^2)))^(gamma/(gamma-1)))*((1/(2*gamma/(gamma+1)*(M1set(jj)^2)*(sind(thetasset(jj))^2))-(gamma-1)/(gamma+1))^(1/(gamma-1)));
        To2set(jj)=To1set(jj);
 end

 %%
%Establish relative flow turn angle and create row vectors to store
%Prandtl-Meyer Function Values (nu2 and nu3)
Delta=thetac;
nu2set=zeros(1,length(Z));
nu3set=zeros(1,length(Z));

%Calculating Prandtl-Meyer Expansion function, Eq. 7.10
 for jj=1:1:length(Z);           
    nu2set(jj)=sqrt((gamma+1)/(gamma-1))*atand(sqrt((gamma-1)/(gamma+1)*(M2set(jj).^2-1)))-atand(sqrt(M2set(jj).^2-1));
    nu3set(jj)=nu2set(jj)+Delta;
 end

%Solving iteratively for Mach number after expansion fan (M3) using
%an assumed range that will cover all Mach numbers during flight
M3=1:0.01:7;
M3set=zeros(1,length(Z));
Mach3Eq=@(nu,M3) sqrt((gamma+1)/(gamma-1))*atand(sqrt((gamma-1)/(gamma+1)*(M3^2-1)))-atand(sqrt(M3^2-1))-nu;

 %Iterative For Loop
 for kk=1:length(nu3set);
    for ii=1:length(M3)
        v=abs(Mach3Eq(nu3set(kk),M3(ii)));
        if round(v*100)/100 < .2 
        M3set(1,kk)=M3(ii);
        break
        end
     end
 end      
M3set;

%%
%Creating row vectors to store post-expansion fan static and stagnation air
%properties.
po3set=zeros(1,length(Z));
To3set=zeros(1,length(Z));
rho3set=zeros(1,length(Z));
p3set=zeros(1,length(Z));
T3set=zeros(1,length(Z));

%Calculating post-expansion fan static and stagnation air
%properties.
for jj=1:1:length(Z)
    po3set(jj)=po2set(jj);
    To3set(jj)=To2set(jj);
    rho3set(jj)=rho2set(jj)*(((1+(gamma-1)/2*(M2set(jj)^2))/(1+(gamma-1)/2*(M3set(jj)^2)))^(1/(gamma-1)));
    p3set(jj)=p2set(jj)*(((1+(gamma-1)/2*(M2set(jj)^2))/(1+(gamma-1)/2*(M3set(jj)^2)))^(gamma/(gamma-1)));
    T3set(jj)=To3set(jj)/(1+(gamma-1)/2*(M3set(jj)^2));
end

%%
%Calculating mass needed per cartridge (mneeded), using 50microliters at STP
vcartridge=0.7*(10^-6);
mneeded=(101300)*(5*10^(-8))/(287*273.15) %(kg)
%%
%Calculating velocity from M3, mdot from rho,A,V
V3set=M3set.*sqrt(gamma*R.*T3set);
mdot=rho3set.*(pi/4)*(.00635^2).*V3set;
%plot(mneeded./mdot, Z)
%%
%Pressure Needed to adequately fill cartridge at given air properties.
pneededset=zeros(1,length(Z));

for jj=1:1:length(Z)
pneededset(jj)=mneeded*R*T3set(jj)/(vcartridge);
end
pneededset;
plot(pneededset, Z, 'r', po3set, Z, 'b');


    

    
    
    
    
    
    
    
    
    
    