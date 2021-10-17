import { NestFactory } from '@nestjs/core';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import { AppModule } from './app.module';
import { IotModule } from './iot/iot.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule, { cors: true });
  const config = new DocumentBuilder()
    .setTitle('Gone With The Fire API')
    .setDescription('RESTful API documentation for Gone With The Fire API')
    .setVersion('1.0')
    .build();

  const swagger = SwaggerModule.createDocument(app, config, {
    include: [IotModule],
  });

  SwaggerModule.setup('/', app, swagger, {
    customSiteTitle: 'Gone With The Fire API',
  });
  await app.listen(5000);
  console.log(`Application is running on: ${await app.getUrl()}`);
}
bootstrap();
