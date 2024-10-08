#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <signal.h>

#include "getDados.h"
#include "gerenciarInv.h"
#include "atualizarInv.h"
#include "mostrarDados.h"

void handle_sigint(int sig) {
    salvarDados(NOME_ARQUIVO);
    
    exit(0);
}

Pessoa pessoas[MAX_PESSOAS];
Data dataAtual;
int quantPessoas = 0;
char tipoInvestimentoString[4][TAM_NOME] = {
    "Prefixado",
    "IPCA+",
    "Selic",
    "CDI"
};

float taxasInvestimentos[] = {
    0.084019, 0.039438, 0.078310, 0.079844, 0.091165, 0.019755, 0.033522, 0.076823, 0.027777, 0.055397, 0.047740,
    0.062887, 0.036478, 0.051340, 0.095223, 0.091620, 0.063571, 0.071730, 0.014160, 0.060697, 0.001630, 0.024289,
    0.013723, 0.080418, 0.015668, 0.040094, 0.012979, 0.010881, 0.099892, 0.021826, 0.051293, 0.083911, 0.061264,
    0.029603, 0.063755, 0.052429, 0.049358, 0.097278, 0.029252, 0.077136, 0.052674, 0.076991, 0.040023, 0.089153,
    0.028331, 0.035246, 0.080772, 0.091903, 0.006976, 0.094933, 0.052600, 0.008606, 0.019221, 0.066323, 0.089023,
    0.034889, 0.006417, 0.002002, 0.045770, 0.006310, 0.023828, 0.097063, 0.090221, 0.085092, 0.026667, 0.053976,
    0.037521, 0.076025, 0.051254, 0.066772, 0.053161, 0.003928, 0.043764, 0.093184, 0.093081, 0.072095, 0.028429,
    0.073853, 0.063998, 0.035405, 0.068786, 0.016597, 0.044010, 0.088008, 0.082920, 0.033034, 0.022897, 0.089337,
    0.035036, 0.068667, 0.095647, 0.058864, 0.065730, 0.085868, 0.043956, 0.092397, 0.039844, 0.081477, 0.068422,
    0.091097, 0.048249, 0.021582, 0.095025, 0.092013, 0.014766, 0.088106, 0.064108, 0.043195, 0.061960, 0.028106,
    0.078600, 0.030746, 0.044703, 0.022611, 0.018753, 0.027623, 0.055644, 0.041650, 0.016961, 0.090680, 0.010317,
    0.012608, 0.049544, 0.076048, 0.098475, 0.093500, 0.068445, 0.038319, 0.074977, 0.036866, 0.029416, 0.023226,
    0.058449, 0.024441, 0.015239, 0.073215, 0.012547, 0.079347, 0.016410, 0.074507, 0.007453, 0.095010, 0.005253,
    0.052156, 0.017621, 0.024006, 0.079780, 0.073265, 0.065656, 0.096741, 0.063946, 0.075973, 0.009348, 0.013490,
    0.052021, 0.007823, 0.006991, 0.020466, 0.046142, 0.081968, 0.057332, 0.075558, 0.005194, 0.015781, 0.099999,
    0.020433, 0.088996, 0.012547, 0.099780, 0.005406, 0.087054, 0.007233, 0.000416, 0.092307, 0.059389, 0.018037,
    0.016313, 0.039169, 0.091303, 0.081970, 0.035910, 0.055249, 0.057943, 0.045258, 0.068739, 0.009964, 0.053081,
    0.075729, 0.030430, 0.099223, 0.057697, 0.087761, 0.074781, 0.062891, 0.003542, 0.074780, 0.083324, 0.092538,
    0.087327, 0.083104, 0.097943, 0.074381, 0.090337, 0.098360, 0.066688, 0.049726, 0.016397, 0.083001, 0.088895,
    0.007699, 0.064971, 0.024804, 0.062948, 0.022914, 0.070062, 0.031687, 0.032878, 0.023143, 0.007416, 0.063307,
    0.022366, 0.065113, 0.051069, 0.097147, 0.028004, 0.054611, 0.071927, 0.011328, 0.047148, 0.059254, 0.094432,
    0.045092, 0.033635, 0.084768, 0.043451, 0.000323, 0.034494, 0.059848, 0.083324, 0.023389, 0.067548, 0.048295,
    0.048194, 0.030496, 0.071209, 0.018256, 0.062182, 0.004086, 0.041398, 0.069598, 0.067394, 0.063764, 0.034712,
    0.018462, 0.060911, 0.062716, 0.073073, 0.032837, 0.074044, 0.020221, 0.092091, 0.068476, 0.065313, 0.025727,
    0.053244, 0.008764, 0.026050, 0.087738, 0.068612, 0.009374, 0.011128, 0.036160, 0.057669, 0.059321, 0.066656,
    0.028878, 0.077577, 0.028838, 0.032964, 0.018975, 0.098436, 0.000358, 0.082739, 0.033148, 0.018820, 0.043650,
    0.095864, 0.091893, 0.076487, 0.069908, 0.012114, 0.068579, 0.038383, 0.077427, 0.094305, 0.091627, 0.086192,
    0.020355, 0.079366, 0.054804, 0.029729, 0.090493, 0.090964, 0.087398, 0.049814, 0.057620, 0.016276, 0.027391,
    0.086458, 0.049240, 0.046366, 0.084894, 0.049598, 0.029105, 0.018042, 0.068418, 0.072755, 0.013906, 0.060311,
    0.049242, 0.083813, 0.072425, 0.017821, 0.022197, 0.049853, 0.012126, 0.013824, 0.036044, 0.032481, 0.093190,
    0.090848, 0.062210, 0.083683, 0.081813, 0.049607, 0.033497, 0.039433, 0.065883, 0.060888, 0.025891, 0.015123,
    0.007255, 0.010785, 0.064721, 0.036360, 0.028827, 0.033139, 0.009115, 0.042733, 0.093449, 0.058357, 0.026546,
    0.065875, 0.076178, 0.048743, 0.015727, 0.088304, 0.062567, 0.051771, 0.020784, 0.055756, 0.042620, 0.082994,
    0.039439, 0.024433, 0.032601, 0.072936, 0.063865, 0.098484, 0.033824, 0.089756, 0.013607, 0.041079, 0.000541,
    0.078328, 0.077439, 0.029368, 0.011467, 0.086553, 0.072101, 0.004916, 0.044911, 0.098647, 0.070791, 0.021088,
    0.047389, 0.086518, 0.009392, 0.009956, 0.038290, 0.030176, 0.065712, 0.080910, 0.013170, 0.005151, 0.005342,
    0.045772, 0.078087, 0.069208, 0.044256, 0.011911, 0.058964, 0.057863, 0.052990, 0.059505, 0.036192, 0.030429, 
    0.088872, 0.047658, 0.016982, 0.060973, 0.052575, 0.061893, 0.059620, 0.023366, 0.082981, 0.007009, 0.009884, 
    0.092373, 0.016965, 0.048173, 0.022549, 0.082677, 0.029083, 0.035719, 0.087828, 0.034425, 0.081491, 0.065915, 
    0.003633, 0.025747, 0.077826, 0.062596, 0.083610, 0.030816, 0.022101, 0.019802, 0.061244, 0.010973, 0.067461, 
    0.078226, 0.071946, 0.020035, 0.040119, 0.031566, 0.043401, 0.023100, 0.038575, 0.053285, 0.015472, 0.055540, 
    0.001458, 0.038021, 0.038217, 0.030541, 0.073741, 0.026044, 0.064966, 0.055232, 0.091959, 0.068599, 0.080979, 
    0.069785, 0.031195, 0.064589, 0.000600, 0.053296, 0.084391, 0.061845, 0.064269, 0.051851, 0.040071, 0.036215, 
    0.071887, 0.080190, 0.067781, 0.015288, 0.003289, 0.006356, 0.068572, 0.018762, 0.061896, 0.070030, 0.056783, 
    0.000113, 0.000571, 0.030524, 0.026157, 0.065537, 0.085756, 0.018116, 0.034135, 0.066734, 0.087901, 0.065330,
    0.031323, 0.088501, 0.018626, 0.015714, 0.050346, 0.082896, 0.067565, 0.090417, 0.019111, 0.039452, 0.070607,
    0.086892, 0.054740, 0.073896, 0.093248, 0.023312, 0.092658, 0.055144, 0.093342, 0.049441, 0.055257, 0.093913, 
    0.079965, 0.081414, 0.059450, 0.065720, 0.099530, 0.093585, 0.032454, 0.087431, 0.058916, 0.063777, 0.075932,
    0.077542, 0.079491, 0.026278, 0.060438, 0.047056, 0.016695, 0.079549, 0.086509, 0.087302, 0.066441, 0.041248,
    0.061198, 0.059690, 0.064560, 0.053856, 0.014834, 0.057902, 0.003296, 0.070091, 0.051815, 0.083261, 0.051505, 
    0.011265, 0.048981, 0.051035, 0.004850, 0.081435, 0.038466, 0.063766, 0.045212, 0.014398, 0.041308, 0.024703, 
    0.040677, 0.001746, 0.071760, 0.057372, 0.081295, 0.058268, 0.044674, 0.047736, 0.099516, 0.005872, 0.007426, 
    0.064077, 0.059728, 0.022260, 0.021979, 0.063024, 0.092351, 0.073794, 0.046285, 0.043856, 0.085059, 0.095266, 
    0.094891, 0.089909, 0.076701, 0.033357, 0.053674, 0.021914, 0.047755, 0.094982, 0.046617, 0.088432, 0.096728, 
    0.018377, 0.045804, 0.078022, 0.076645, 0.090478, 0.025759, 0.076161, 0.096350, 0.033185, 0.040238, 0.056078,
    0.055445, 0.062217, 0.019103, 0.047796, 0.036011, 0.065388, 0.091652, 0.021069, 0.060654, 0.086543, 0.010978,
    0.037356, 0.019900, 0.064652, 0.059269, 0.067655, 0.059634, 0.005886, 0.056087, 0.056362, 0.024263, 0.001891,
    0.034384, 0.000907, 0.092369, 0.060143, 0.077069, 0.088720, 0.093327, 0.017306, 0.044798, 0.048772, 0.079523,
    0.063901, 0.096568, 0.015534, 0.029289, 0.088220, 0.036603, 0.089943, 0.074764, 0.047581, 0.027299, 0.094664,
    0.012233, 0.086568, 0.062319, 0.071867, 0.092454, 0.018407, 0.028228, 0.016717, 0.020298, 0.062613, 0.017624,
    0.012667, 0.022755, 0.094692, 0.001387, 0.016082, 0.011999, 0.046185, 0.064855, 0.091522, 0.010086, 0.061423,
    0.007056, 0.039375, 0.049643, 0.043658, 0.029318, 0.024407, 0.091239, 0.056616, 0.019071, 0.003472, 0.043184,
    0.081390, 0.075338, 0.035638, 0.099797, 0.003567, 0.052355, 0.020095, 0.066179, 0.069979, 0.032762, 0.088934,
    0.064671, 0.034148, 0.005017, 0.076670, 0.080333, 0.069871, 0.068192, 0.090419, 0.031294, 0.075248, 0.029793, 
    0.080937, 0.018906, 0.059111, 0.005344, 0.010145, 0.015728, 0.024415, 0.013617, 0.058912, 0.005805, 0.088955, 
    0.094550, 0.005602, 0.092522, 0.046905, 0.025697, 0.058701, 0.016884, 0.058459, 0.047635, 0.081555, 0.092607,
    0.052652, 0.058225, 0.072940, 0.022524, 0.026417, 0.063358, 0.053818, 0.001665, 0.093152, 0.034755, 0.020571,
    0.052263, 0.040099, 0.030717, 0.067990, 0.064513, 0.044334, 0.026902, 0.070319, 0.033289, 0.021452, 0.075921,
    0.025811, 0.068357, 0.001618, 0.084512, 0.085241, 0.060076, 0.032148, 0.066796, 0.052683, 0.084800, 0.025021,
    0.025623, 0.007324, 0.051438, 0.088981, 0.061141, 0.053103, 0.082133, 0.095896, 0.073675, 0.034396, 0.035994,
    0.004392, 0.002386, 0.000508, 0.048725, 0.029289, 0.070826, 0.082015, 0.050741, 0.046747, 0.007826, 0.019098,
    0.048365, 0.092338, 0.004339, 0.008441, 0.024486, 0.071135, 0.061124, 0.009286, 0.096157, 0.086747, 0.016609, 
    0.047595, 0.075728, 0.077750, 0.000698, 0.057861, 0.073646, 0.074373, 0.092257, 0.009640, 0.078764, 0.094644, 
    0.010148, 0.027490, 0.023932, 0.080974, 0.009504, 0.074673, 0.027721, 0.017330, 0.093771, 0.076086, 0.009668, 
    0.098111, 0.084527, 0.034154, 0.069246, 0.045651, 0.043440, 0.065403, 0.032398, 0.060049, 0.012998, 0.008127, 
    0.037800, 0.013696, 0.065988, 0.011446, 0.088068, 0.058245, 0.021086, 0.066833, 0.052888, 0.031234, 0.094322, 
    0.076821, 0.012209, 0.003826, 0.051494, 0.039930, 0.021157, 0.045265, 0.016016, 0.030825, 0.043376, 0.000543, 
    0.064979, 0.012622, 0.046195, 0.008418, 0.078025, 0.078593, 0.068468, 0.091023, 0.086720, 0.006267, 0.004718, 
    0.052707, 0.017713, 0.092787, 0.010952, 0.038800, 0.059619, 0.063841, 0.070034, 0.053941, 0.040662, 0.082243, 
    0.057768, 0.092155, 0.022173, 0.078924, 0.037420, 0.038189, 0.009749, 0.080796, 0.038732, 0.074728, 0.093418, 
    0.084927, 0.083146, 0.071443, 0.063520, 0.051614, 0.062466, 0.050240, 0.057881, 0.067184, 0.002948, 0.075595, 
    0.059971, 0.013900, 0.014394, 0.019590, 0.077741, 0.084428, 0.073531, 0.018403, 0.066671, 0.031299, 0.010558, 
    0.088843, 0.010223, 0.047978, 0.027032, 0.019972, 0.028774, 0.065764, 0.094700, 0.022192, 0.050691, 0.077846, 
    0.093635, 0.014212, 0.029460, 0.056101, 0.064452, 0.087341, 0.023285, 0.067400, 0.062936, 0.083255, 0.081300,
    0.077330, 0.002845, 0.059041, 0.061758, 0.076376, 0.077443, 0.028429, 0.007675, 0.088001, 0.017272, 0.017899,
    0.035979, 0.044304, 0.037871, 0.064752, 0.010069, 0.032571, 0.086944, 0.060760, 0.010417, 0.080579, 0.074972,
    0.039878, 0.036680, 0.039424, 0.027219, 0.059964, 0.006823, 0.090155, 0.043220, 0.088123, 0.067485, 0.046065, 
    0.047164, 0.029243, 0.022442, 0.024607, 0.057672, 0.030117, 0.012608, 0.074944, 0.048016, 0.048587, 0.019249,
    0.085887, 0.013339, 0.029317, 0.018458, 0.000283, 0.090077, 0.028875, 0.080862, 0.065049, 0.068753, 0.017541,
    0.004473, 0.095972, 0.077506, 0.011296, 0.086126, 0.020726
};

void exibirMenu() {
    printf("\n================== Menu ==================\n");
    printf(" 1. Criar nova pessoa e finança\n");
    printf(" 2. Adicionar finança a uma pessoa\n");
    printf(" 3. Modificar finança de uma pessoa\n");
    printf(" 4. Mostrar finanças de uma pessoa\n");
    printf(" 5. Deletar finanças de uma pessoa\n");
    printf(" 6. Mostrar uma finança de uma pessoa\n");
    printf(" 7. Ordenar finanças por data\n");
    printf(" 8. Ordenar finanças por tipo\n");
    printf(" 9. Ordenar finanças por valor\n");
    printf("10. Agrupar por tipo e ordenar por data\n");
    printf("11. Agrupar por tipo e ordenar por valor\n");
    printf("12. Atualizar investimento\n");
    printf("13. Exibir valor bruto total\n");
    printf("14. Exibir valor líquido total\n");
    printf(" 0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    signal(SIGINT, handle_sigint);
    int opcao, idPessoa, indexFinanca;

    recuperarDados(NOME_ARQUIVO);

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        
        limparEntrada();

        switch (opcao) {
            case 0: {                // Sair
                printf("Saindo...\n");
                salvarDados(NOME_ARQUIVO);
                exit(0);
            }
            case 1: {                // Criar nova pessoa e finança
                criarPessoaEFinanca();
                break;
            }
            case 2: {                // Adicionar finança a uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                while (idPessoa < -1 || idPessoa >= quantPessoas) {
                    printf("ID inválido. Digite de novo ou digite -1 para voltar ao menu:\n> ");
                    scanf("%d", &idPessoa);
                    if (idPessoa == -1) break;
                }
                if (idPessoa != -1) adicionarFinanca(idPessoa);
                break;
            }
            case 3: {                // Modificar finança de uma pessoa
                printf("Digite o ID da pessoa (ou -1 para voltar):\n> ");
                scanf("%d", &idPessoa);

                while (idPessoa < -1 || idPessoa >= quantPessoas) {
                    printf("ID inválido. Digite de novo:\n> ");
                    scanf("%d", &idPessoa);
                }
                if (idPessoa == -1) break;

                printf("Digite o índice da finança (ou -1 para voltar):\n> ");
                scanf("%d", &indexFinanca);
                
                while (indexFinanca < -1 || indexFinanca >= pessoas[idPessoa].quantFinancas) {
                    printf("Digite um índice válido ou -1 para voltar:\n> ");
                    scanf("%d", &indexFinanca);
                }
                if (indexFinanca == -1) break;


                modificarFinanca(idPessoa, indexFinanca);
                break;
            }
            case 4: {                // Mostrar finanças de uma pessoa
                printf("Digite o ID da pessoa (-1 para voltar):\n> ");
                scanf("%d", &idPessoa);
                while (idPessoa < -1 || idPessoa >= quantPessoas) {
                    printf("ID inválido. Digite de novo ou digite -1 para voltar ao menu:\n> ");
                    scanf("%d", &idPessoa);
                }
                if (idPessoa != -1) mostrarFinancasPessoas(pessoas[idPessoa]);
                break;
            }
            case 5: {                // Deletar finança de uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                while (idPessoa < -1 || idPessoa >= quantPessoas) {
                    printf("ID inválido. Digite de novo ou digite -1 para voltar ao menu:\n> ");
                    scanf("%d", &idPessoa);
                    if (idPessoa == -1) break;
                }
                if (idPessoa != -1) {
                    printf("Digite o índice da finança:\n> ");
                    scanf("%d", &indexFinanca);
                }

                while (indexFinanca < -1 || indexFinanca >= pessoas[idPessoa].quantFinancas) {
                    printf("Digite um índice válido ou -1 para voltar:\n> ");
                    scanf("%d", &indexFinanca);
                    if (indexFinanca == -1) break;
                }
                
                if (idPessoa != -1 && indexFinanca != -1) deletarFinanca(&pessoas[idPessoa], indexFinanca);
                
                break;
            }
            case 6: {                // Mostrar uma finança de uma pessoa
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                while (idPessoa < -1 || idPessoa >= quantPessoas) {
                    printf("ID inválido. Digite de novo ou digite -1 para voltar ao menu:\n> ");
                    scanf("%d", &idPessoa);
                    if (idPessoa == -1) break;
                }

                if (idPessoa != -1) {
                    printf("Digite o índice da finança:\n> ");
                    scanf("%d", &indexFinanca);
                }

                while (indexFinanca < -1 || indexFinanca >= pessoas[idPessoa].quantFinancas) {
                    printf("Digite um índice válido ou -1 para voltar:\n> ");
                    scanf("%d", &indexFinanca);
                    if (indexFinanca == -1) break;
                }
                if (idPessoa != -1 && indexFinanca != -1)
                    mostrarUmaFinancaDeUmaPessoa(pessoas[idPessoa].financas[indexFinanca]);

                break;
            }
            case 7: {               // Ordenar finanças por data
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorData(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 8: {                // Ordenar finanças por tipo
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorTipo(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 9: {                // Ordenar finanças por valor
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    ordenarFinancasPorValor(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 10: {                // Agrupar por tipo e ordenar por data
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    agruparEOrdenarFinancasData(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 11: {                // Agrupar por tipo e ordenar por valor
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                if (idPessoa < 0 || idPessoa >= quantPessoas) {
                    printf("ID de pessoa inválido.\n");
                } else {
                    agruparEOrdenarFinancasValor(&pessoas[idPessoa]);
                    mostrarFinancasPessoas(pessoas[idPessoa]);
                }
                break;
            }
            case 12: {              // atualizar investimento
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                atualizarInvestimento(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            case 13: {              // valor bruto total
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                imprimirValorBrutoTotal(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            case 14: {              // valor bruto total
                printf("Digite o ID da pessoa:\n> ");
                scanf("%d", &idPessoa);
                printf("Digite o índice da finança:\n> ");
                scanf("%d", &indexFinanca);
                imprimirValorLiquidoTotal(&pessoas[idPessoa].financas[indexFinanca]);
                break;
            }
            default: {
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
        }
    }

    return 0;
}
