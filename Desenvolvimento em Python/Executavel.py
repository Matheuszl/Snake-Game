import pygame, random
from pygame.locals import *

#Este jogo foi desevolvido no intuito de aprender mais sobre a linguagem
#Aprendiz de: https://www.youtube.com/watch?v=H4TXHI9BRCQ&list=LLP3zwBUBDERBYfK1l72bpkA&index=3&t=0s

#a funcao permite que a maça fique alinhada a matriz da tela
def maca_in_matriz():
    x = random.randint(0,390)
    y = random.randint(0,390)
    return (x//10 * 10, y//10 * 10) #a divisao inteira nao deixa num ficar quebrado


#a funcao permite colisao entre os objetos
def collision(c1, c2):
    return (c1[0] == c2[0]) and (c1[1] == c2[1])

UP = 0
LEFT = 3
RIGHT = 1
DOWN = 2

pontos = 0

pygame.init()
screen = pygame.display.set_mode((400,400)) #tamanho da tela
pygame.display.set_caption('executavel')


snake = [(200, 200), (210, 200), (220, 200)]
snake_skin = pygame.Surface((10,10))
snake_skin.fill((255,255,255))

apple_pos = maca_in_matriz() #posiçao aleatoria para a maça
apple = pygame.Surface((10,10)) #390 ultimo lugar da tela
apple.fill((255,0,0))
my_direction = LEFT

#Vamos limitar a valocidade da cobra(FPS)
velocidade = pygame.time.Clock()

while True: #criaçao da tela até o fechamento
    velocidade.tick(20)#Define a velocidade a 20FPS
    for event in pygame.event.get(): #pega atravez de um evento
        if event.type == QUIT:
            pygame.quit()
        #vamos contolar as direcoes:
        if event.type == KEYDOWN:
            if event.key == K_UP:
                my_direction = UP
            if event.key == K_DOWN:
                my_direction = DOWN
            if event.key == K_LEFT:
                my_direction = LEFT
            if event.key == K_RIGHT:
                my_direction = RIGHT

    if collision(snake[0], apple_pos):
        apple_pos = maca_in_matriz()
        pontos = pontos + 1
        print(pontos)
        snake.append((0,0))

    for i in range(len(snake) - 1, 0, -1):
        snake[i] = (snake[i-1][0], snake[i-1][1])

    if my_direction == UP: #A sequencia de ifs mexe a cabeca da cobra
        snake[0] = (snake[0][0], snake[0][1] -10)
    if my_direction == DOWN:
        snake[0] = (snake[0][0], snake[0][1] +10)
    if my_direction == RIGHT:
        snake[0] = (snake[0][0] + 10, snake[0][1])
    if my_direction == LEFT:
        snake[0] = (snake[0][0] - 10, snake[0][1])

    screen.fill((0,0,0))
    screen.blit(apple, apple_pos)

    for pos in snake:
        screen.blit(snake_skin, pos)
    pygame.display.update()
