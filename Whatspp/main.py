from whatsapp_api_client_python import API
from src import config

import email
import imaplib
from email.header import decode_header

poster = API.GreenApi(config.ID_INSTANCE, config.API_TOKEN_INSTANCE)


def sendFile(path: str, name: str):
    result = poster.sending.sendFileByUpload(config.chatId, path, name)


def handler(message):
    if message["From"] is not None:
        mail_from = decode_header(message["From"])[0][0].decode()
    else:
        mail_from = None
    if message["Subject"] is not None:
        mail_subject = decode_header(message["Subject"])[0][0].decode()
    else:
        mail_subject = None

    if message.is_multipart():
        for part in message.walk():
            if part.get_content_disposition() == 'attachment':
                name = decode_header(part.get_filename())[0][0].decode()
                with open(name, 'wb') as f:
                    f.write(part.get_payload(decode=True))
                #sendFile(name, name)
                return True
    return False


def receive():
    mail = imaplib.IMAP4_SSL(config.SERVER)
    mail.login(config.EMAIL, config.PASSWORD)
    mail.select('inbox')
    res, data = mail.uid("search", "UNSEEN", "ALL")
    if len(data) != 0:
        mail_ids = []
        for block in data:
            mail_ids += block.split()

        for i in mail_ids:
            status, data = mail.fetch(i, '(RFC822)')
            for response_part in data:
                if isinstance(response_part, tuple):
                    message = email.message_from_bytes(response_part[1])
                    if handler(message):
                        mail.store(i, '+FLAGS', '\\Seen')


if __name__ == '__main__':
    receive()
