import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { Iot } from './iot/entities/iot.entity';
import { IotModule } from './iot/iot.module';

@Module({
  imports: [
    IotModule,
    TypeOrmModule.forRoot({
      type: 'mysql',
      host: 'sce-hackathon-db.mysql.database.azure.com',
      port: 3306,
      username: 'naterpotatoers@sce-hackathon-db',
      password: 'TiconderogaHB#2',
      database: 'sce_hackathon',
      entities: [Iot],
      synchronize: true,
    }),
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
