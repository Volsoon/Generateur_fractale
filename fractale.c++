#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>

const int hauteur_image = 600;
const int largeur_image = 600;
const float x_max = 1.5;
const float ratio = 2*x_max/largeur_image;
const std::complex<float> c(-0.8,0.156);
// const std::complex<float> c(0.2875,0.758);


std::complex<float> pixel_to_complexe(const int l, const int h){
    const float x = (l-largeur_image/2)*ratio;
    const float y = -(h-hauteur_image/2)*ratio;
    return std::complex<float>(x, y);
}

int nb_etapes_sortie(std::complex<float> z){
    int i = 0;
    while (i < 20 and abs(z)<2) {
        i++;
        z = z*z + c;
    }
    return i;
}

// generate image
int main(){
    std::ofstream image;
    
    image.open("fractale.ppm");

    if(image.is_open()){
        // image header
        image << "P3" << '\n';
        image << hauteur_image << " " << largeur_image << '\n';
        image << "255" << '\n';

        for(int y=0; y < hauteur_image; y++){
            for(int x=0; x < largeur_image; x++){
                std::complex<float> z = pixel_to_complexe(x, y);
                int i = nb_etapes_sortie(z);
                int intensite = 255*i/20;
                image << intensite << " " << int(intensite*0.75) << " " << int(intensite*0.25) << '\n';
            }
        }
    }

    image.close();
    return 0;
}