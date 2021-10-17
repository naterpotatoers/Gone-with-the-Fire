import { Entity, Column, PrimaryGeneratedColumn, PrimaryColumn } from 'typeorm';

@Entity()
export class Iot {
  @PrimaryColumn()
  id: string;

  @Column({ default: 0 })
  temperature: number;

  @Column({ default: 0 })
  humidity: number;

  @Column({ default: 0 })
  longitude: number;

  @Column({ default: 0 })
  latitude: number;

  @Column({ default: false })
  smoke: boolean;
}
