# qDiscordTextBot
Набросал для своих нужд небольшой бот для дискорда на Qt
Используются WebSocket(https://discord.com/developers/docs/topics/gateway) + Rest Api(https://discord.com/developers/)
Обрабатывает текстовые сообщения, использует на входе стратегию(наследуемую от discordBotAbstractStrategy)
Для примера - простейшая стратегия Echo отвечающая, наверное выложу еще небольшой пример.

Для функционирования необходимо создать приложение -> создать в нем бота -> получить api ключ -> передать боту ключик и написать/воспользоваться стратегию обработки сообщений(см main.cpp)
!(https://sun9-35.userapi.com/s/v1/if2/zN88DaEtJv5HlAMGLDWdMNBTdpOV0rTxja3e37df92Cub7TRhHm2-o5G784oPMkRh8XqTl7wWISFCUBi2dUxKCIh.jpg?size=282x305&quality=96&type=album)
