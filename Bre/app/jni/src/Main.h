//
// Created by Jonathan on 26/09/2024.
//

#ifndef BRE_MAIN_H
#define BRE_MAIN_H

/**
 *  Per permettere ad un file C di poter leggere un progetto C++, è necessario creare un file .h, come
 *  ponte tra i due linguaggi, che abbia esattamente la seguente sintassi:
 */

#ifdef __cplusplus
extern "C" {
#endif

int main_in_cpp();

#ifdef __cplusplus
}
#endif

#endif //BRE_MAIN_H
